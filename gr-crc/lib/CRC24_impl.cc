/**
 * @file CRC24_impl.cc
 * @brief This file holds the whole data processing of this block.
 * @author Ranisavljevic Daniel
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "CRC24_impl.h"
#include <string>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>

static unsigned int crc24q[256] = {0};

using namespace std;

namespace gr {
  namespace crc {

    /**
    * @brief shared_ptr
    */
    CRC24::sptr
    /**
    * @brief crc::USB_sink::make is the public interface for creating new instances.
    */
    CRC24::make(int msglength, bool check)
    {
      return gnuradio::get_initial_sptr
        (new CRC24_impl(msglength, check));
    }

   /**
   * @brief private constructor for sync block
   * @param none
   * @return nothing
   */
    CRC24_impl::CRC24_impl(int msglength, bool check)
      : gr::block("CRC24",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(char))),
              mlen(msglength),
              d_check(check)
    {
         
    }

   /**
   * @brief virtual destructor
   * @param none
   * @return nothing
   */
    CRC24_impl::~CRC24_impl()
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
    int CRC24_impl::general_work (int noutput_items,
                                  gr_vector_int &ninput_items,
                                  gr_vector_const_void_star &input_items,
                                  gr_vector_void_star &output_items)
    {
      char *in = (char *) input_items[0];
      char *out = (char *) output_items[0];
      int flen=strlen(in);
      string crc;
      string msg(in);



      
      if(d_check) //check crc
      {
         if((flen%(mlen+24))!=0)
         {
            cerr << "CRC24 Block: MSG length parameter invalid (length of input stream must be divisible by MSG length parameter)" <<endl;
            return -1;
         }
         int msgcrcnum=(int)(flen/(mlen+24));
         string s1;
         string smsg;
         string res1;
         for(int i=0; i<msgcrcnum;i++)
         {
           s1=msg.substr(i*(mlen+24),(mlen+24));
          // cout<<s1<<"len:"<<s1.length()<<"num:"<<msgcrcnum<<endl;
           string crcmsg=s1.substr(s1.length()-24,24); //filter checksum
           smsg=msg.substr(i*(mlen+24),mlen);
           crc=crc24_calc(smsg);
           if(crcmsg!=crc) //compare the calculated checksum with original
           {
              cout<<"CRC24 Block: MSG "<<i+1<<": CRC mismatch!"<<endl;
              return -1;
           }
           else
           {
              cout<<"CRC24 Block: MSG "<<i+1<<": CRC check successful!"<<endl;
           }
         }
         //if check successful, output the whole input 
         strcpy(out,in);
         
      }
      else  //calculate checksum
      {
         if((flen%mlen)!=0)
         {
            cerr << "CRC24 Block: MSG length parameter invalid (length of input stream must be divisible by MSG length parameter)" <<endl;
            return -1;
         }
         int msgnum=(int)(flen/mlen);
         string s2;
         string res2;
         //calculate crc for every message
         for(int i=0; i<msgnum;i++)
         {
           s2=msg.substr(i*mlen,mlen);
           crc=crc24_calc(s2);
           s2+=crc;
           res2+=s2;
         }

         strcpy(out,res2.c_str());
      }
      consume(0,strlen(in)); //consume data from input stream 0
      return strlen(out);
    }
    
   /**
   * @brief This function calculates the CRC sum.
   * @param data: Message that is secured with the CRC sum.
   * @param len: Length of the data packet.
   * @return CRC sum
   */
   string CRC24_impl::crc24_calc(string data)
   {
      string crc;
      unsigned int temp1,temp2,temp3;
      string spoly;
      temp1=temp2=temp3=0;
      //convert CRC polynom to binary
      bitset<24>cp(CRCPOLY);
      spoly=cp.to_string();
      //extend data for checksum
      data=data+(bitset<24>(0).to_string());
      //calculate checksum
      for(int j = 0; j < data.length()-24;j++)
      {
           if(data[j] == '1')
           {
               for(int k = 0; k < spoly.length(); k++)
               {
                  temp1=(int)data[j+k]-48;
                  temp2=(int)spoly[k]-48;
                  temp3=(int)(temp2^temp1);
                  data[j+k]=(char)(temp3 + 48);
               }
           }
      }
      //copy last 24 characters to crc string
      crc=data.substr(data.length()-24,data.length());
      return crc;
   }

  } /* namespace crc */
} /* namespace gr */

