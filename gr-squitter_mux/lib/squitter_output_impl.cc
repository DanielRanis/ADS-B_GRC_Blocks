/**
 * @file squitter_output_impl.cc
 * @brief This file holds the whole data processing of this block.
 * @author Ranisavljevic Daniel
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

//Includes
#include <gnuradio/io_signature.h>
#include "squitter_output_impl.h"

using namespace rapidxml;
using namespace std;

namespace gr {
  namespace squitter_mux {

    /**
    * @brief shared_ptr
    */
    squitter_output::sptr
    /**
    * @brief squitter_mux::squitter_output::make is the public interface for creating new instances.
    */
    squitter_output::make(const float alpha_param,
                          const int pw_param,
                          const int sr_param,
                          const int span_param,
                          const int sps_param,
                          const int imx_param,
                          const int md,
                          const int testmsg)
    {
      return gnuradio::get_initial_sptr
        (new squitter_output_impl(alpha_param,pw_param,sr_param,span_param,sps_param,imx_param,md,testmsg));
    }

    /**
    * @brief private constructor for sync block
    * @param none
    * @return nothing
    */
    squitter_output_impl::squitter_output_impl(const float alpha_param,
                                               const int pw_param,
                                               const int sr_param,
                                               const int span_param,
                                               const int sps_param,
                                               const int imx_param,
                                               const int md,
                                               const int testmsg)
   :gr::block("squitter_output",
              gr::io_signature::make(2, 2, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(char))),
              alpha(alpha_param),
              pw(pw_param),
              sr(sr_param),
              imx(imx_param),
              sps(sps_param),
              span(span_param),
              mode(md),
              tmsg(testmsg)
    { }

    /**
    * @brief virtual destructor
    * @param none
    * @return nothing
    */
    squitter_output_impl::~squitter_output_impl()
    {
    }
    

    /**
    * @brief Work function
    * @param noutput_items: Amount of output items that should be created.
    * @param ninput_items: Amount of items that are currently in the input stream (not used).
    * @param input_items: Address of input items.
    * @param output_items: Address of output items.
    * @return Amount of output items that were created.
    */
    int squitter_output_impl::general_work (int noutput_items,
                                            gr_vector_int &ninput_items,
                                            gr_vector_const_void_star &input_items,
                                            gr_vector_void_star &output_items)
    {
        char *in_data = ( char *) input_items[0]; //first input stream
        char *in_time = ( char *) input_items[1]; //second input stream
        char *out = (char *) output_items[0]; //output stream
        string binary;
        
        char preamble[PRE_LEN+1]={0};
        char timing[BUF_LEN+1]={0};
        
        const char node_names[4][14]={"squitter_apos","squitter_gpos","squitter_avel","squitter_aid"};
        int err=0; //error variable
        unsigned int a_param=0;
        int sq_cnt=0;
        int stat=0;
        
        xml_document <> doc;  //xml object
        xml_node<> * r_node;  //root node
        xml_node<> * rep_node;  //repetition node
        xml_node<> * s1_node;  //first sub node
        xml_node<> * s2_node;  //second sub node
        
        usleep(1000); //wait some time till data is ready
        
        /*  FILTER PARAMETERS VALIDATION  */
        if(alpha < MIN_ALPHA or alpha > MAX_ALPHA)
        {
           cout << "Additional Data Block: Filter parameter (Alpha) is invalid !"
                << "(type: float, range=[" << MIN_ALPHA << "," << MAX_ALPHA << "])" << endl;
           err=1;
        }
        if(pw < MIN_PWIDTH or pw > MAX_PWIDTH)
        {
            cout << "Additional Data Block: Filter parameter (Pulsewidth) is invalid!"
                 << "(type: integer, range=[" << MIN_PWIDTH << "," << MAX_PWIDTH << "])" << endl;
           err=1;
        }
        if(sr < MIN_SR or sr > MAX_SR)
        {
           cout << "Additional Data Block: Filter parameter (Samplerate) is invalid!"
                << "(type: integer, range=[" << MIN_SR << "," << MAX_SR << "])" << endl;
           err=1;
        }
        if(imx < MIN_IMX or imx > MAX_IMX)
        {
           cout << "Additional Data Block: Filter parameter (Maximum Current Imax) is invalid!"
                << "(type: integer, range=[" << MIN_IMX << "," << MAX_IMX << "])" << endl;
           err=1;
        }
        if(span < MIN_SPAN or span > MAX_SPAN)
        {
           cout << "Additional Data Block: Filter parameter (Span) is invalid!"
                << "(type: integer, range=[" << MIN_SPAN << "," << MAX_SPAN << "])" << endl;
           err=1;
        }
        if(sps < MIN_SPS or sps > MAX_SPS)
        {
           cout << "Additional Data Block: Filter parameter (Sps) is invalid!"
                << "(type: integer, range=[" << MIN_SPS << "," << MAX_SPS << "])" << endl;
           err=1;
        }
        if(tmsg < MIN_TMSG or tmsg > (int)MAX_TMSG)
        {
           cout << "Additional Data Block: Test-Message is invalid!"
                << "(type: integer, range=[" << MIN_TMSG << "," << MAX_TMSG << "])" << endl;
           err=1;
        }
        //error occured
        if(err==1)
        {
           return -1;
        }
        
        
        //set message identification
        out[0]=(char)mode+'0';
        
        //set message
        if(mode==2 or mode==1)
        {
          /* FILTER PARAMETER CONVERSION */
          //convert alpha parameter to integer representation (correction factor = 1000)
          a_param=(unsigned int)round(alpha*CORRFACT);
          binary=bitset<ALPHA_SIZE>(a_param).to_string();
          strcat(out,binary.c_str());
          //other filter parameters 
          binary=bitset<PWIDTH_SIZE>(pw).to_string();
          strcat(out,binary.c_str());
          
          binary=bitset<SR_SIZE>(sr).to_string();
          strcat(out,binary.c_str());
          
          binary=bitset<SPAN_SIZE>(span).to_string();
          strcat(out,binary.c_str());
          
          binary=bitset<SPS_SIZE>(sps).to_string();
          strcat(out,binary.c_str());
          
          binary=bitset<IMX_SIZE>(imx).to_string();
          strcat(out,binary.c_str());
        }
        
        if(mode==1)
        {
          binary=bitset<TMSG_SIZE>(tmsg).to_string();
          strcat(out,binary.c_str());
        }
        
        if(mode==2)
        {
          /* XML parsing */
          //parse second input stream
          doc.parse<0>(&in_time[0]);
          
          /* ---------- FIND AND CHECK ROOT NODES ---------- */
          if((r_node=doc.first_node("ADS_B_simulator")) == 0)
          {
             cerr << "Additional Data Block: XML file error: root node 'ADS_B_simulator' is not included" << endl;
             return -1;
          }
          if((s1_node=r_node->first_node("aircraft")) == 0)
          {
             cerr << "Additional Data Block: XML file error: root node 'aircraft' is not included" << endl;
             return -1;
          }
          if((s2_node=s1_node->first_node("ADS_message")) == 0)
          {
             cerr << "Additional Data Block: XML file error: root node 'ADS_message' is not included" << endl;
             return -1;
          }
          
          /* ---------- CODING OF TIMING INFORMATION ---------- */
          
          if((time_coding(timing,r_node,(int)sizeof(timing),"repetition"))==-1)
          {
            return -1;
          }
          //output repetition information
          strcat(out,timing);
          for(int i=0; i<4; i++)
          {
             if((stat=time_coding(timing,s2_node,(int)sizeof(timing),node_names[i]))==-1)
             {
               return -1;
             }
             else if(stat==-2)
             {
               sq_cnt++;
             }
             //no squitter found
             if(sq_cnt==4)
             {
                cerr << "Additional Data Block: XML file error: No squitter defined in XML file" << endl;
                return -1;
             }
             //output timing information
             strcat(out,timing);
          }
          /* ---------- PREAMBLE CODING ---------- */
          if((preamble_coding(preamble,s1_node,(int)sizeof(preamble)))==-1)
          {
            return -1;
          }
          //output preamble
          strcat(out,preamble);
          //output frame
          strcat(out,in_data);
        }
        
        doc.clear();
        consume(0,strlen(in_data)); //consume data from input stream 0
        consume(1,strlen(in_time)); //consume data from input stream 1

        return strlen(out); //return produced data
    }
    
    int squitter_output_impl::preamble_coding(char* pbuf, xml_node<> * r_node, int preamble_size)
    {
       //check parameter
       if((PRE_LEN+1) != preamble_size)
       {
          cerr << "Additional Data Block: preamble coding function: parameters are inconsistent"<<endl;
          return -1;
       }
       
        //clear destination buffer
        memset(pbuf,0,preamble_size);
        
        xml_node<> * t;  //temporary node
        string binary;
        long int num =(long int) 0;
        
        if((t=r_node->first_node("preamble")) != 0)
        {
           //get value
           if((sscanf(t->value(),"%lx",&num))!=1 or strpbrk(t->value(),",.") != NULL or num < MIN_PRE or num > MAX_PRE)
           {
              cerr << "Additional Data Block: preamble coding function: "
                   << "XML file error: 'preamble' has wrong format (type: integer, range: ["
                   << MIN_PRE <<","<< MAX_PRE <<"])" << endl;
              return -1;
           }
           binary=bitset<PRE_LEN>(num).to_string();
           //store binary representation into preamble buffer
           strcat(pbuf,binary.c_str());
        }
        else
        {
           cerr << "Additional Data Block: preamble coding function: "
                << "XML file error: 'preamble' is not included!" <<endl;
           return -1;
        }
        return 0;
    }
    
    int squitter_output_impl::time_coding(char* buf,xml_node<> * r_node,int buf_size, const char* node)
    {
        //check parameter
        if((BUF_LEN+1) != buf_size)
        {
           cerr << "Additional Data Block: time coding function: parameters are inconsistent"<<endl;
           return -1;
        }
        //clear destination buffer
        memset(buf,0,buf_size);
        
        xml_node<> * t; //temporary node
        long int num =(long int) 0;
        string binary;
        static int sq_cnt=(int)0;
        
        /* ---- REPETITION CODING ---- */
        if(strcmp(node,"repetition")==0)
        {
            //get time information
            if((t=r_node->first_node(node)) != 0)
            {
               //get value
               if((sscanf(t->value(),"%ld",&num))!=1 or strpbrk(t->value(),",.") != NULL or num < MIN_TIME or num > MAX_TIME)
               {
                  cerr << "Additional Data Block: time coding function: "
                       << "XML file error: time information of '"<< node <<"' has wrong format (type: integer, range: ["
                       << MIN_TIME <<","<< MAX_TIME <<"])" << endl;
                  return -1;
               }
               binary=bitset<BUF_LEN>(num).to_string();
               //store binary representation into preambel buffer
               strcat(buf,binary.c_str());
            }
            else
            {
                cerr << "Additional Data Block: time coding function: "
                     << "XML file error: 'repetition' is not included!" <<endl;
                return -1;
            }
            
          return 0;
        }
       
        
        /* ---- SQUITTER TIME INFORMATION ---- */
        if((t=r_node->first_node(node)) != 0)
        {
            if((t=t->first_node("time")) != 0)
            {
                 //get value
                if((sscanf(t->value(),"%ld",&num))!=1 or strpbrk(t->value(),",.") != NULL or num < MIN_TIME or num > MAX_TIME)
                {
                   cerr << "Additional Data Block: time coding function: "
                        << "XML file error: time information of '"<< node <<"' has wrong format (type: integer, range: ["
                        << MIN_TIME <<","<< MAX_TIME <<"])" << endl;
                   return -1;
                }
                binary=bitset<BUF_LEN>(num).to_string();
                //store binary representation into preambel buffer
                strcat(buf,binary.c_str());
            }
            else
            {
               cerr << "Additional Data Block: time coding function: "
                    << "XML file error: time information of '"<< node <<"' is not included!" <<endl;
               return -1;
            }
        }
        else
        {
          return -2;
        }
        
      return 0;
    }
  } /* namespace squitter_mux */
} /* namespace gr */

