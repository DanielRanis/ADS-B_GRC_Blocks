/* -*- c++ -*- */
/* 
 * Copyright 2017 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "packaging_impl.h"



using namespace std;
using namespace rapidxml;

namespace gr {
  namespace xml_decoder {

    packaging::sptr
    packaging::make()
    {
      return gnuradio::get_initial_sptr
        (new packaging_impl());
    }

    /*
     * The private constructor
     */
    packaging_impl::packaging_impl()
      : gr::block("packaging",
              gr::io_signature::make(1 ,1, sizeof(char)), //inputs
              gr::io_signature::make(1, 1, sizeof(char))) //outputs
    {}

    /*
     * Our virtual destructor.
     */
    packaging_impl::~packaging_impl()
    {
    }
    
    void packaging_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
       ninput_items_required[0] = noutput_items;
    }
    
    int packaging_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        char *in = (char*) input_items[0];
        char *out = (char *) output_items[0];
       
        //Binary buffers
        char header[H_LEN+1]={0};      //header buffer (binary representation)
        char apos_even[MSG_LEN+1]={0}; //apos squitter buffer (even binary representation)
        char apos_odd[MSG_LEN+1]={0};  //apos squitter buffer (odd binary representation)
        char gpos_even[MSG_LEN+1]={0}; //gpos squitter buffer (even binary representation)
        char gpos_odd[MSG_LEN+1]={0};  //gpos squitter buffer (odd binary representation)
        char avel[MSG_LEN+1]={0};      //avel squitter buffer (binary representation)
        char aid[MSG_LEN+1]={0};       //aid squitter buffer (binary representation)

        //FRAME buffer
        char FRAME[FRAME_LEN+1]={0};
        
        //XML variables
        xml_document <> doc;   //xml object
        xml_node<> * r_node;   //root node
        xml_node<> * h_node;   //header root node
        xml_node<> * sq_node;  //squitter root node
        xml_node<> * t;

        //variables
        float tr[TR_ELEMENTS];
        string binary;
        int sq_stat=0;
        int sq_cnt=(int)0;
        char* asciistr=NULL;

        //prepare transition look-up table
        transition(&tr[0]);
        
        //alocate memory for the temporary input buffer
        char *in_temp=(char*)calloc(strlen(in),sizeof(char));
        if(in_temp==NULL)
        {
           cerr << "ADS Message Block: Error in function: general_work(): Memory allocation" <<endl;
           return -1;
        }
        /* --------------- XML PARSING --------------- */
        //copy input stream into temporary stream
        memcpy((char*)in_temp,(char*)in,strlen(in));
        //parse input stream
        doc.parse<0>(&in_temp[0]);
        /* ---------- FIND AND CHECK ROOT NODES ---------- */
        if((r_node=doc.first_node("ADS_B_simulator")) == 0) 
        {
           cerr << "ADS Message Block: XML file error: root node 'ADS_B_simulator' is not included" << endl;
           return -1;
        }
        if((h_node=r_node->first_node("aircraft")) == 0)
        {
           cerr << "ADS Message Block: XML file error: root node 'aircraft' is not included" << endl;
           return -1;
        } 
        if((sq_node=h_node->first_node("ADS_message")) == 0)
        {
           cerr << "ADS Message Block: XML file error: root node 'ADS_message' is not included" << endl;
           return -1;
        }
        
        /* ---------- FRAME CODING ---------- */
        //header
        if(header_coding(&header[0],h_node,(int)sizeof(header))==-1)
        {
           return -1;
        }
        //squitter apos
        if((sq_stat=apos_coding(&apos_even[0],&apos_odd[0],sq_node,&tr[0],(int)sizeof(apos_even),(int)sizeof(apos_odd)))==-1)
        {
           return -1;
        }
        else if(sq_stat==1)
        {
           sq_cnt++;
        }
        //squitter gpos
        if((sq_stat=gpos_coding(&gpos_even[0],&gpos_odd[0],sq_node,&tr[0],(int)sizeof(gpos_even),(int)sizeof(gpos_odd)))==-1)
        {
           return -1;
        }
        else if(sq_stat==1)
        {
           sq_cnt++;
        }
        //squitter avel
        if((sq_stat=avel_coding(&avel[0],sq_node,(int)sizeof(avel)))==-1)
        {
           return -1;
        }
        else if(sq_stat==1)
        {
           sq_cnt++;
        }
        //squitter avel
        if((sq_stat=aid_coding(&aid[0],sq_node,(int)sizeof(aid)))==-1)
        {
           return -1;
        }
        else if(sq_stat==1)
        {
           sq_cnt++;
        }
        
        //no squitter found
        if(sq_cnt==4)
        {
           cerr << "ADS Message Block: XML file error: No squitter defined in XML file" << endl;
           return -1;
        }
            
        /* ---------- FRAME BUILDING ---------- */
        /* |H|APOS_EVEN|H|APOS_ODD|H|GPOS_EVEN|H|GPOS_ODD|H|AVEL|H|AID| */
        strcat(FRAME,header);
        strcat(FRAME,apos_even);
        strcat(FRAME,header);
        strcat(FRAME,apos_odd);
        strcat(FRAME,header);
        strcat(FRAME,gpos_even);
        strcat(FRAME,header);
        strcat(FRAME,gpos_odd);
        strcat(FRAME,header);
        strcat(FRAME,avel);
        strcat(FRAME,header);
        strcat(FRAME,aid);
        
        /* OUTPUT FRAME */
        strcpy(out,FRAME);
        /* CLEAN UP */
        doc.clear();
        free(in_temp);
        
        // Tell runtime system how many input items were consumed
        consume (0,strlen(in));

        // Tell runtime system how many output items were produced
        return strlen(out);
    }
    
    int packaging_impl::header_coding(char* hbuf, xml_node<> * r_node, int header_size)
    {
        if((H_LEN+1) != header_size)
        {
          cerr << "ADS Message Block: Header coding function: parameters are inconsistent!"<<endl;
          return -1;
        }
        //clear destination buffer
        memset(hbuf,0,header_size);
        
        xml_node<> * t;   //temporary node
        string binary;
        long int num=(long int)0;
        
        /* --------------- HEADER CODING --------------- */
              /* ---------- DATAFORMAT ---------- */
              if((t=r_node->first_node("dataformat")) != 0)
              {
                 //get value
                 if((sscanf(t->value(),"%ld",&num))!=1 or strpbrk(t->value(),",.") != NULL or num < MIN_DF or num > MAX_DF)
                 {
                    cerr << "ADS Message Block: XML file error: 'dataformat' has wrong format!"
                         << "(type: integer, range: ["<< MIN_DF <<","<< MAX_DF <<"])" << endl;
                    return -1;
                 }
                 binary=bitset<5>(num).to_string();
                 //store binary representation into header buffer
                 strcat(hbuf,binary.c_str());
              }
              else
              {
                 cerr << "ADS Message Block: XML file error: 'dataformat' is not included!" << endl;
                 return -1;
              }
              
              /* ---------- CA ---------- */
              if((t=r_node->first_node("CA")) != 0)
              {
                 //get value 
                 if((sscanf(t->value(),"%ld",&num))!=1 or strpbrk(t->value(),",.") != NULL or num < MIN_CA or num > MAX_CA)
                 {
                    cerr << "ADS Message Block: XML file error: 'CA' has wrong format!"
                         << "(type: integer, range: ["<< MIN_CA <<","<< MAX_CA <<"])" << endl;
                    return -1;
                 }
                 binary=bitset<3>(num).to_string();
                 //store binary representation into header buffer
                 strcat(hbuf,binary.c_str());
              }
              else
              {
                 cerr << "ADS Message Block: XML file error: 'CA' is not included!" << endl;
                 return -1;
              }
              
              /* ---------- AIRCRAFT ADDRESS ---------- */
              if((t=r_node->first_node("aircraft_address")) != 0)
              {
                 //get value
                 if((sscanf(t->value(),"%lx",&num))!=1 or strpbrk(t->value(),",.") != NULL or num < MIN_AC_ADDR or num > MAX_AC_ADDR)
                 {
                    cerr << "ADS Message Block: XML file error: 'aircraft_address' has wrong format!"
                         << "(type: integer, range: ["<< MIN_AC_ADDR <<","<< MAX_AC_ADDR <<"])" << endl;
                    return -1;
                 }
                 binary=bitset<24>(num).to_string();
                 //store binary representation into header buffer
                 strcat(hbuf,binary.c_str());
              }
              else
              {
                 cerr << "ADS Message Block: XML file error: 'aircraft_address' is not included!" << endl;
                 return -1;
              }
       return 0;
    }
    
    int packaging_impl::apos_coding(char* aposbuf_even,char* aposbuf_odd,xml_node<> * r_node,float* tr,int apos_even_size, int apos_odd_size)
    {
        if((MSG_LEN+1)!=apos_even_size or (MSG_LEN+1)!=apos_odd_size)
        {
          cerr << "ADS Message Block: Apos coding function: parameters are inconsistent!"<<endl;
          return -1;
        }
        
        //clear destination buffers
        memset(aposbuf_even,0,apos_even_size);
        memset(aposbuf_odd,0,apos_odd_size);
        
        xml_node<> * t;   //temporary node
        xml_node<> * s;   //sub node
       
        string binary;
        long int num=(long int)0;
        float fnum=(float)0;
        float rlat=(float)0;
           /* ---------- SQUITTER AIRBONE POSITION SUBNODE ---------- */
           if((s=r_node->first_node("squitter_apos")) != 0)
           {
              /* ---------- FORMAT TYPE ---------- */
              if((t=s->first_node("format_type")) != 0)
              {
                 //get and check value
                 if((sscanf(t->value(),"%ld",&num))!=1 or strpbrk(t->value(),",.") != NULL or num < MIN_AF or num > MAX_AF)
                 {
                    cerr << "ADS Message Block: XML file error: Squitter apos: 'format_type' has wrong format!"
                         << "(type: integer, range: ["<< MIN_AF <<","<< MAX_AF <<"])" << endl;
                    return -1;
                 }
                 binary=bitset<5>(num).to_string();
                 //store binary representation into apos buffer
                 strcpy(aposbuf_even,binary.c_str());
                 strcpy(aposbuf_odd,binary.c_str());
              }
              else
              {
                 cerr << "ADS Message Block: XML file error: Squitter apos: 'format_type' is not included!" << endl;
                 return -1;
              }
              /* ---------- SURVEILLANCE STATUS ---------- */
              if((t=s->first_node("surveillance")) != 0)
              {
                 //get and check value
                 if((sscanf(t->value(),"%ld",&num))!=1 or strpbrk(t->value(),",.") != NULL or num < MIN_SRV_ST or num > MAX_SRV_ST)
                 {
                    cerr << "ADS Message Block: XML file error: Squitter apos: 'surveillance' has wrong format!"
                         << "(type: integer, range: ["<< MIN_SRV_ST <<","<< MAX_SRV_ST <<"])" << endl;
                    return -1;
                 }
                 binary=bitset<2>(num).to_string();
                 //store binary representation into apos buffer
                 strcat(aposbuf_even,binary.c_str());
                 strcat(aposbuf_odd,binary.c_str());
              }
              else
              {
                 cerr << "ADS Message Block: XML file error: Squitter apos: 'surveillance status' is not included!" << endl;
                 return -1;
              }
              /* ---------- ANTENNA ---------- */
              if((t=s->first_node("antenna")) != 0)
              {
                 //get and check value
                 if((sscanf(t->value(),"%ld",&num))!=1 or strpbrk(t->value(),",.") != NULL or num < MIN_ANT or num > MAX_ANT)
                 {
                    cerr << "ADS Message Block: XML file error: Squitter apos: 'antenna' has wrong format!"
                         << "(type: integer, range: ["<< MIN_ANT <<","<< MAX_ANT <<"])" << endl;
                    return -1;
                 }
                 binary=bitset<1>(num).to_string();
                 //store binary representation into apos buffer
                 strcat(aposbuf_even,binary.c_str());
                 strcat(aposbuf_odd,binary.c_str());
              }
              else
              {
                 cerr << "ADS Message Block: XML file error: Squitter apos: 'antenna' is not included!" << endl;
                 return -1;
              }
              /* ---------- ALTITUDE ---------- */
              if((t=s->first_node("altitude")) != 0)
              {
                 //get and check value
                 if((sscanf(t->value(),"%ld",&num))!=1 or strpbrk(t->value(),",.") != NULL or
                    (num % 25) != 0 or (num % 100) != 0 or num < MIN_ALT or num > MAX_ALT)
                 {
                    cerr << "ADS Message Block: XML file error: Squitter apos: 'altitude' has wrong format!"
                         << "(type: integer, range: ["<< MIN_ALT <<","<< MAX_ALT <<"])" << endl;
                    return -1;
                 }
                 //code altitude
                 num=(int)(num+1000)/25;
                 binary=bitset<12>(num).to_string();
                 //store binary representation into apos buffer
                 strcat(aposbuf_even,binary.c_str());
                 strcat(aposbuf_odd,binary.c_str());
              }
              else
              {
                 cerr << "ADS Message Block: XML file error: Squitter apos: 'altitude' is not included!" << endl;
                 return -1;
              }
              /* ---------- TIME UTC ---------- */
              if((t=s->first_node("time_UTC")) != 0)
              {
                 //get and check value
                 if((sscanf(t->value(),"%ld",&num))!=1 or strpbrk(t->value(),",.") != NULL or num < MIN_T_UTC or num > MAX_T_UTC)
                 {
                    cerr << "ADS Message Block: XML file error: Squitter apos: 'time_UTC' has wrong format!"
                         << "(type: integer, range: ["<< MIN_T_UTC <<","<< MAX_T_UTC <<"])" << endl;
                    return -1;
                 }
                 binary=bitset<1>(num).to_string();
                 //store binary representation into apos buffer
                 strcat(aposbuf_even,binary.c_str());
                 strcat(aposbuf_odd,binary.c_str());
              }
              else
              {
                 cerr << "ADS Message Block: XML file error: Squitter apos: 'time_UTC' is not included!" << endl;
                 return -1;
              }
              /* ---------- LATITUDE ---------- */
              if((t=s->first_node("latitude")) != 0)
              {
                 long int cpr_lat_even,cpr_lat_odd;
                 cpr_lat_even=cpr_lat_odd=0;
                 //get and check value
                 if((sscanf(t->value(),"%f",&fnum))!=1 or fnum < MIN_LAT or fnum > MAX_LAT)
                 {
                    cerr << "ADS Message Block: XML file error: Squitter apos: 'latitude' has wrong format!"
                         << "(type: integer, range: ["<< MIN_LAT <<","<< MAX_LAT <<"])" << endl;
                    return -1;
                 }
                 //cpr coding (latitude, even and odd)
                 if((cpr_lat_even=(long int)cpr_lat(fnum,0,&rlat))==-1)
                 {
                    cerr << "ADS Message Block: Squitter apos: CPR coding error (latitude, even)!" << endl;
                    return -1;
                 }
                 if((cpr_lat_odd=(long int)cpr_lat(fnum,1,&rlat))==-1)
                 {
                    cerr << "ADS Message Block: Squitter apos: CPR coding error (latitude, odd)!" << endl;
                    return -1;
                 }
                 
                 //EVEN MESSAGE
                 //add cpr format (0, even) to temporary buffer
                 binary=bitset<1>(0).to_string();
                 strcat(aposbuf_even,binary.c_str());
                 //convert to binary representation
                 binary=bitset<17>(cpr_lat_even).to_string();
                 //store binary representation into apos even buffer
                 strcat(aposbuf_even,binary.c_str());
                 
                 //ODD MESSAGE
                 //add cpr format (1, odd) to temporary buffer
                 binary=bitset<1>(1).to_string();
                 strcat(aposbuf_odd,binary.c_str());
                 //convert to binary representation
                 binary=bitset<17>(cpr_lat_odd).to_string();
                 //store binary representation into apos odd buffer
                 strcat(aposbuf_odd,binary.c_str());
              }
              else
              {
                 cerr << "ADS Message Block: XML file error: Squitter apos: 'latitude' is not included!" << endl;
                 return -1;
              }
              /* ---------- LONGITUDE ---------- */
              if((t=s->first_node("longitude")) != 0)
              {
                 long int cpr_lon_even,cpr_lon_odd;
                 cpr_lon_even=cpr_lon_odd=0;
                 float rlat=(float)0;
                 //get and check value
                 if((sscanf(t->value(),"%f",&fnum))!=1 or fnum < MIN_LON or fnum > MAX_LON)
                 {
                    cerr << "ADS Message Block: XML file error: Squitter apos: 'longitude' has wrong format!"
                         << "(type: float, range: ["<< MIN_LON <<","<< MAX_LON <<"])" << endl;
                    return -1;
                 }
                 //cpr coding (longitude, even and odd)
                 if((cpr_lon_even=(long int)cpr_lon(fnum,0,&tr[0],rlat))==-1)
                 {
                    cerr << "ADS Message Block: Squitter apos: CPR coding error (longitude, even)!" << endl;
                    return -1;
                 }
                 if((cpr_lon_odd=(long int)cpr_lon(fnum,1,&tr[0],rlat))==-1)
                 {
                    cerr << "ADS Message Block: Squitter apos: CPR coding error (longitude, even)!" << endl;
                    return -1;
                 }
                 
                 //EVEN MESSAGE
                 //convert to binary representation
                 binary=bitset<17>(cpr_lon_even).to_string();
                 //store binary representation into apos even buffer
                 strcat(aposbuf_even,binary.c_str());
                 
                 //ODD MESSAGE
                 //convert to binary representation
                 binary=bitset<17>(cpr_lon_odd).to_string();
                 //store binary representation into apos odd buffer
                 strcat(aposbuf_odd,binary.c_str());
              }
              else
              {
                 cerr << "ADS Message Block: XML file error: Squitter apos: 'latitude' is not included!" << endl;
                 return -1;
              }
           }
           else
           {
              return 1;
           }
       return 0;
    }
    
    int packaging_impl::gpos_coding(char* gposbuf_even,char* gposbuf_odd,xml_node<> * r_node,float* tr,int gpos_even_size, int gpos_odd_size)
    {
        if((MSG_LEN+1)!=gpos_even_size or (MSG_LEN+1)!=gpos_odd_size)
        {
          cerr << "ADS Message Block: Gpos coding function: parameters are inconsistent!"<<endl;
          return -1;
        }
        //clear destination buffers
        memset(gposbuf_even,0,gpos_even_size);
        memset(gposbuf_odd,0,gpos_odd_size);
        
        xml_node<> * t;   //temporary node
        xml_node<> * s;   //sub node
        string binary;
        long int num=(long int)0;
        float fnum=(float)0;
        float rlat=(float)0;
           /* ---------- SQUITTER GROUND POSITION SUBNODE ---------- */
           if((s=r_node->first_node("squitter_gpos")) != 0)
           {
              /* ---------- FORMAT TYPE ---------- */
              if((t=s->first_node("format_type")) != 0)
              {
                 //get and check value
                 if((sscanf(t->value(),"%ld",&num))!=1 or strpbrk(t->value(),",.") != NULL or num < MIN_GF or num > MAX_GF)
                 {
                    cerr << "ADS Message Block: XML file error: Squitter gpos: 'format_type' has wrong format!"
                         << "(type: integer, range: ["<< MIN_GF <<","<< MAX_GF <<"])" << endl;
                    return -1;
                 }
                 binary=bitset<5>(num).to_string();
                 //store binary representation into gpos buffer
                 strcpy(gposbuf_even,binary.c_str());
                 strcpy(gposbuf_odd,binary.c_str());
              }
              else
              {
                 cerr << "ADS Message Block: XML file error: Squitter gpos: 'format_type' is not included!" << endl;
                 return -1;
              }
              
              /* ---------- MOVEMENT ---------- */
              if((t=s->first_node("movement")) != 0)
              {
                 //get and check value
                 if((sscanf(t->value(),"%ld",&num))!=1 or strpbrk(t->value(),",.") != NULL or num < MIN_MV or num > MAX_MV)
                 {
                    cerr << "ADS Message Block: XML file error: Squitter gpos: 'movement' has wrong format!"
                         << "(type: integer, range: ["<< MIN_MV <<","<< MAX_MV <<"])" << endl;
                    return -1;
                 }
                 binary=bitset<7>(num).to_string();
                 //store binary representation into gpos buffer
                 strcat(gposbuf_even,binary.c_str());
                 strcat(gposbuf_odd,binary.c_str());
              }
              else
              {
                 cerr << "ADS Message Block: XML file error: Squitter gpos: 'movement' is not included!" << endl;
                 return -1;
              }
              
              /* ---------- STATUS ---------- */
              if((t=s->first_node("status")) != 0)
              {
                 //get and check value
                 if((sscanf(t->value(),"%ld",&num))!=1 or strpbrk(t->value(),",.") != NULL or num < MIN_ST or num > MAX_ST)
                 {
                    cerr << "ADS Message Block: XML file error: Squitter gpos: 'status' has wrong format!"
                         << "(type: integer, range: ["<< MIN_ST <<","<< MAX_ST <<"])" << endl;
                    return -1;
                 }
                 binary=bitset<1>(num).to_string();
                 //store binary representation into gpos buffer
                 strcat(gposbuf_even,binary.c_str());
                 strcat(gposbuf_odd,binary.c_str());
              }
              else
              {
                 cerr << "ADS Message Block: XML file error: Squitter gpos: 'status' is not included!" << endl;
                 return -1;
              }
              
              /* ---------- GROUND TRACK ---------- */
              if((t=s->first_node("ground_track")) != 0)
              {
                 //get and check value
                 if((sscanf(t->value(),"%f",&fnum))!=1 or fnum < MIN_GT or fnum > MAX_GT)
                 {
                    cerr << "ADS Message Block: XML file error: Squitter gpos: 'ground_track' has wrong format!"
                         << "(type: float, range: ["<< MIN_GT <<","<< MAX_GT <<"])" << endl;
                    return -1;
                 }
                 //angular weighted binary numeral
                 num=(long int)round(((float)127/360)*fnum);
                 binary=bitset<7>(num).to_string();
                 //store binary representation into gpos buffer
                 strcat(gposbuf_even,binary.c_str());
                 strcat(gposbuf_odd,binary.c_str());
              }
              else
              {
                 cerr << "ADS Message Block: XML file error: Squitter gpos: 'ground_track' is not included!" << endl;
                 return -1;
              }
              
              /* ---------- TIME UTC ---------- */
              if((t=s->first_node("time_UTC")) != 0)
              {
                 //get and check value
                 if((sscanf(t->value(),"%ld",&num))!=1 or strpbrk(t->value(),",.") != NULL or num < MIN_T_UTC or num > MAX_T_UTC)
                 {
                    cerr << "ADS Message Block: XML file error: Squitter gpos: 'time_UTC' has wrong format!"
                         << "(type: integer, range: ["<< MIN_T_UTC <<","<< MAX_T_UTC <<"])" << endl;
                    return -1;
                 }
                 binary=bitset<1>(num).to_string();
                 //store binary representation into gpos buffer
                 strcat(gposbuf_even,binary.c_str());
                 strcat(gposbuf_odd,binary.c_str());
              }
              else
              {
                 cerr << "ADS Message Block: XML file error: Squitter gpos: 'time_UTC' is not included!" << endl;
                 return -1;
              }
              /* ---------- LATITUDE ---------- */
              if((t=s->first_node("latitude")) != 0)
              {
                 long int cpr_lat_even,cpr_lat_odd;
                 cpr_lat_even=cpr_lat_odd=0;
                 //get and check value
                 if((sscanf(t->value(),"%f",&fnum))!=1 or fnum < MIN_LAT or fnum > MAX_LAT)
                 {
                    cerr << "ADS Message Block: XML file error: Squitter gpos: 'latitude' has wrong format!"
                         << "(type: float, range: ["<< MIN_LAT <<","<< MAX_LAT <<"])" << endl;
                    return -1;
                 }
                 //cpr coding (latitude, even and odd)
                 if((cpr_lat_even=(long int)cpr_lat(fnum,0,&rlat))==-1)
                 {
                    cerr << "ADS Message Block: Squitter gpos: CPR coding error (latitude, even)!" << endl;
                    return -1;
                 }
                 if((cpr_lat_odd=(long int)cpr_lat(fnum,1,&rlat))==-1)
                 {
                    cerr << "ADS Message Block: Squitter gpos: CPR coding error (latitude, odd)!" << endl;
                    return -1;
                 }
                 
                 //EVEN MESSAGE
                 //add cpr format (0, even) to gpos even buffer
                 binary=bitset<1>(0).to_string();
                 strcat(gposbuf_even,binary.c_str());
                 //convert to binary representation
                 binary=bitset<17>(cpr_lat_even).to_string();
                 //store binary representation into gpos even buffer
                 strcat(gposbuf_even,binary.c_str());
                 
                 //ODD MESSAGE
                 //add cpr format (1, odd) to gpos odd buffer
                 binary=bitset<1>(1).to_string();
                 strcat(gposbuf_odd,binary.c_str());
                 //convert to binary representation
                 binary=bitset<17>(cpr_lat_odd).to_string();
                 //store binary representation into gpos odd buffer
                 strcat(gposbuf_odd,binary.c_str());
              }
              else
              {
                 cerr << "ADS Message Block: XML file error: Squitter gpos: 'latitude' is not included!" << endl;
                 return -1;
              }
              
              /* ---------- LONGITUDE ---------- */
              if((t=s->first_node("longitude")) != 0)
              {
                 long int cpr_lon_even,cpr_lon_odd;
                 cpr_lon_even=cpr_lon_odd=0;
                 float rlat=(float)0;
                 //get and check value
                 if((sscanf(t->value(),"%f",&fnum))!=1 or fnum < MIN_LON or fnum > MAX_LON)
                 {
                    cerr << "ADS Message Block: XML file error: Squitter gpos: 'longitude' has wrong format!"
                         << "(type: float, range: ["<< MIN_LON <<","<< MAX_LON <<"])" << endl;
                    return -1;
                 }
                 //cpr coding (longitude, even and odd)
                 if((cpr_lon_even=(long int)cpr_lon(fnum,0,&tr[0],rlat))==-1)
                 {
                    cerr << "ADS Message Block: Squitter gpos: CPR coding error (longitude, even)!" << endl;
                    return -1;
                 }
                 if((cpr_lon_odd=(long int)cpr_lon(fnum,1,&tr[0],rlat))==-1)
                 {
                    cerr << "ADS Message Block: Squitter gpos: CPR coding error (longitude, even)!" << endl;
                    return -1;
                 }
                 
                 //EVEN MESSAGE
                 //convert to binary representation
                 binary=bitset<17>(cpr_lon_even).to_string();
                 //store binary representation into apos even buffer
                 strcat(gposbuf_even,binary.c_str());
                 
                 //ODD MESSAGE
                 //convert to binary representation
                 binary=bitset<17>(cpr_lon_odd).to_string();
                 //store binary representation into apos odd buffer
                 strcat(gposbuf_odd,binary.c_str());
              }
              else
              {
                 cerr << "ADS Message Block: Squitter gpos: 'longitude' is not included!" << endl;
                 return -1;
              }
           }
           else
           {
              return 1;
           }
        return 0;
    }
    
    int packaging_impl::avel_coding(char* avelbuf,xml_node<> * r_node, int avel_size)
    {
        if((MSG_LEN+1)!=avel_size)
        {
          cerr << "ADS Message Block: Avel coding function: parameters are inconsistent!"<<endl;
          return -1;
        }
        //clear destination buffers
        memset(avelbuf,0,avel_size);
        
        xml_node<> * t;   //temporary node
        xml_node<> * s;   //sub node
        string binary;
        
        long int num=(long int)0;
        float fnum=(float)0;
        int stype=(int)0;
           /* ---------- SQUITTER AIRCRAFT VELOCITY SUBNODE ---------- */
           if((s=r_node->first_node("squitter_avel")) != 0)
           {
              /* ---------- FORMAT TYPE ---------- */
              if((t=s->first_node("format_type")) != 0)
              {
                 //get and check value
                 if((sscanf(t->value(),"%ld",&num))!=1 or strpbrk(t->value(),",.") != NULL or num < MIN_VF or num > MAX_VF)
                 {
                    cerr << "ADS Message Block: XML file error: Squitter avel: 'format_type' has wrong format!"
                         << "(type: integer, range: ["<< MIN_VF <<","<< MAX_VF <<"])" << endl;
                    return -1;
                 }
                 binary=bitset<5>(num).to_string();
                 //store binary representation into avel buffer
                 strcpy(avelbuf,binary.c_str());
              }
              else
              {
                 cerr << "ADS Message Block: XML file error: Squitter avel: 'format_type' is not included!" << endl;
                 return -1;
              }
              
              /* ---------- SUB TYPE ---------- */
              if((t=s->first_node("subtype")) != 0)
              {
                 //get and check value
                 if((sscanf(t->value(),"%d",&stype))!=1 or strpbrk(t->value(),",.") != NULL or stype < MIN_STY or stype > MAX_STY)
                 {
                    cerr << "ADS Message Block: XML file error: Squitter avel: 'subtype' has wrong format!"
                         << "(type: integer, range: ["<< MIN_STY <<","<< MAX_STY <<"])" << endl;
                    return -1;
                 }
                 binary=bitset<3>(stype).to_string();
                 //store binary representation into avel buffer
                 strcat(avelbuf,binary.c_str());
              }
              else
              {
                 cerr << "ADS Message Block: XML file error: Squitter avel: 'subtype' is not included!" << endl;
                 return -1;
              }
              
              /* ---------- INTENT CHANGE FLAG ---------- */
              if((t=s->first_node("ICF")) != 0)
              {
                 //get and check value
                 if((sscanf(t->value(),"%ld",&num))!=1 or strpbrk(t->value(),",.") != NULL or num < MIN_ICF or num > MAX_ICF)
                 {
                    cerr << "ADS Message Block: XML file error: Squitter avel: 'ICF' has wrong format!"
                         << "(type: integer, range: ["<< MIN_ICF <<","<< MAX_ICF <<"])" << endl;
                    return -1;
                 }
                 binary=bitset<1>(num).to_string();
                 //store binary representation into avel buffer
                 strcat(avelbuf,binary.c_str());
              }
              else
              {
                 cerr << "ADS Message Block: XML file error: Squitter avel: 'ICF' is not included!" << endl;
                 return -1;
              }
              
              /* ---------- IFR CAPABILITY FLAG ---------- */
              if((t=s->first_node("IFR")) != 0)
              {
                 //get and check value
                 if((sscanf(t->value(),"%ld",&num))!=1 or strpbrk(t->value(),",.") != NULL or num < MIN_IFR or num > MAX_IFR)
                 {
                    cerr << "ADS Message Block: XML file error: Squitter avel: 'IFR' has wrong format!"
                         << "(type: integer, range: ["<< MIN_IFR <<","<< MAX_IFR <<"])" << endl;
                    return -1;
                 }
                 binary=bitset<1>(num).to_string();
                 //store binary representation into avel buffer
                 strcat(avelbuf,binary.c_str());
              }
              else
              {
                 cerr << "ADS Message Block: XML file error: Squitter avel: 'IFR' is not included" << endl;
                 return -1;
              }
              
              /* ---------- VELOCITY UNCERTAINITY ---------- */
              if((t=s->first_node("v_uncertainity")) != 0)
              {
                 //get and check value
                 if((sscanf(t->value(),"%ld",&num))!=1 or strpbrk(t->value(),",.") != NULL or num < MIN_VUNC or num > MAX_VUNC)
                 {
                    cerr << "ADS Message Block: XML file error: Squitter avel: 'v_uncertainity' has wrong format!"
                         << "(type: integer, range: ["<< MIN_VUNC <<","<< MAX_VUNC <<"])" << endl;
                    return -1;
                 }
                 binary=bitset<3>(num).to_string();
                 //store binary representation into avel buffer
                 strcat(avelbuf,binary.c_str());
              }
              else
              {
                 cerr << "ADS Message Block: XML file error: Squitter avel: 'v_uncertainity' is not included!" << endl;
                 return -1;
              }
              
             /* ---------- GROUND SPEED ENCODING ---------- */
             if(stype==1 or stype==2)
             {
                 /* ---------- EAST - WEST VELOCITY ---------- */
                 if((t=s->first_node("ew_velocity")) != 0)
                 {
                    //get and check value
                    if((sscanf(t->value(),"%ld",&num))!=1 or strpbrk(t->value(),",.") != NULL or num < MIN_V or num > MAX_V)
                    {
                      cerr << "ADS Message Block: XML file error: Squitter avel: 'ew_velocity' has wrong format!"
                           << "(type: integer, range: ["<< MIN_V <<","<< MAX_V <<"])" << endl;
                      return -1;
                    }
                    //set east-west velocity sign
                    binary=bitset<1>(1).to_string();
                    //store binary representation into avel buffer
                    strcat(avelbuf,binary.c_str());
                    binary=bitset<10>(num).to_string();
                    //store binary representation into avel buffer
                    strcat(avelbuf,binary.c_str());
                 }
                 /* ---------- WEST - EAST VELOCITY ---------- */
                 else if((t=s->first_node("we_velocity")) != 0)
                 {
                    //get and check value
                    if((sscanf(t->value(),"%ld",&num))!=1 or strpbrk(t->value(),",.") != NULL or num < MIN_V or num > MAX_V)
                    {
                      cerr << "ADS Message Block: XML file error: Squitter avel: 'we_velocity' has wrong format!"
                           << "(type: integer, range: ["<< MIN_V <<","<< MAX_V <<"])" << endl;
                      return -1;
                    }
                    //set west-east velocity sign
                    binary=bitset<1>(0).to_string();
                    //store binary representation into avel buffer
                    strcat(avelbuf,binary.c_str());
                    binary=bitset<10>(num).to_string();
                    //store binary representation into avel buffer
                    strcat(avelbuf,binary.c_str());
                 }
                 else
                 {
                   cerr << "ADS Message Block: XML file error: Squitter avel: 'ew_velocity' and 'ew_velocity' are not included!" << endl;
                   return -1;
                 }
                 
                 /* ---------- NORTH - SOUTH VELOCITY ---------- */
                 if((t=s->first_node("ns_velocity")) != 0)
                 {
                    //get and check value
                    if((sscanf(t->value(),"%ld",&num))!=1 or strpbrk(t->value(),",.") != NULL or num < MIN_V or num > MAX_V)
                    {
                      cerr << "ADS Message Block: XML file error: Squitter avel: 'ns_velocity' has wrong format!"
                           << "(type: integer, range: ["<< MIN_V <<","<< MAX_V <<"])" << endl;
                      return -1;
                    }
                    //set north-south velocity sign
                    binary=bitset<1>(1).to_string();
                    //store binary representation into avel buffer
                    strcat(avelbuf,binary.c_str());
                    binary=bitset<10>(num).to_string();
                    //store binary representation into avel buffer
                    strcat(avelbuf,binary.c_str());
                 }
                 /* ---------- SOUTH - NORTH VELOCITY ---------- */
                 else if((t=s->first_node("sn_velocity")) != 0)
                 {
                    //get and check value
                    if((sscanf(t->value(),"%ld",&num))!=1 or strpbrk(t->value(),",.") != NULL or num < MIN_V or num > MAX_V)
                    {
                      cerr << "ADS Message Block: XML file error: Squitter avel: 'sn_velocity' has wrong format!"
                           << "(type: integer, range: ["<< MIN_V <<","<< MAX_V <<"])" << endl;
                      return -1;
                    }
                    //set south-north velocity sign
                    binary=bitset<1>(0).to_string();
                    //store binary representation into avel buffer
                    strcat(avelbuf,binary.c_str());
                    binary=bitset<10>(num).to_string();
                    //store binary representation into avel buffer
                    strcat(avelbuf,binary.c_str());
                 }
                 else
                 {
                   cerr << "ADS Message Block: XML file error: Squitter avel: 'sn_velocity' and 'ns_velocity' are not included!" << endl;
                   return -1;
                 }
             }
             
             /* ---------- AIR SPEED ENCODING ---------- */
             if(stype==3 or stype==4)
             {
                 /* ---------- DIRECTION ---------- */
                 if((t=s->first_node("direction")) != 0)
                 {
                    //get and check value
                    if((sscanf(t->value(),"%f",&fnum))!=1 or fnum < MIN_DIR or fnum > MAX_DIR)
                    {
                      cerr << "ADS Message Block: XML file error: Squitter avel: 'direction' has wrong format!"
                           << "(type: float, range: ["<< MIN_DIR <<","<< MAX_DIR <<"])" << endl;
                      return -1;
                    }
                    //set direction sign
                    binary=bitset<1>(1).to_string();
                    //store binary representation into avel buffer
                    strcat(avelbuf,binary.c_str());
                    num=(long int)ceil((fnum/(float)360)*1024);
                    binary=bitset<10>(num).to_string();
                    //store binary representation into avel buffer
                    strcat(avelbuf,binary.c_str());
                 }
                 //direction information is not available
                 else
                 {
                    //set direction sign
                    binary=bitset<1>(0).to_string();
                    //store binary representation into avel buffer
                    strcat(avelbuf,binary.c_str());
                    num=(long int)0;
                    binary=bitset<10>(num).to_string();
                    //store binary representation into avel buffer
                    strcat(avelbuf,binary.c_str());
                 }
                 
                 /* ---------- INDICATED AIRSPEED ---------- */
                 if((t=s->first_node("ias_velocity")) != 0)
                 {
                    //get and check value
                    if((sscanf(t->value(),"%ld",&num))!=1 or strpbrk(t->value(),",.") != NULL or num < MIN_IAS or num > MAX_IAS)
                    {
                      cerr << "ADS Message Block: XML file error: Squitter avel: 'ias_velocity' has wrong format!"
                           << "(type: integer, range: ["<< MIN_IAS <<","<< MAX_IAS <<"])" << endl;
                      return -1;
                    }
                    //set ias sign
                    binary=bitset<1>(0).to_string();
                    //store binary representation into avel buffer
                    strcat(avelbuf,binary.c_str());
                    binary=bitset<10>(num).to_string();
                    //store binary representation into avel buffer
                    strcat(avelbuf,binary.c_str());
                 }
                 /* ---------- TRUE AIRSPEED ---------- */
                 else if((t=s->first_node("tas_velocity")) != 0)
                 {
                    //get and check value
                    if((sscanf(t->value(),"%ld",&num))!=1 or strpbrk(t->value(),",.") != NULL or num < MIN_TAS or num > MAX_TAS)
                    {
                      cerr << "ADS Message Block: XML file error: Squitter avel: 'tas_velocity' has wrong format!"
                           << "(type: integer, range: ["<< MIN_TAS <<","<< MAX_TAS <<"])" << endl;
                      return -1;
                    }
                    //set tas sign
                    binary=bitset<1>(1).to_string();
                    //store binary representation into avel buffer
                    strcat(avelbuf,binary.c_str());
                    binary=bitset<10>(num).to_string();
                    //store binary representation into avel buffer
                    strcat(avelbuf,binary.c_str());
                 }
                 //no velocity information included
                 else
                 {
                   cerr << "ADS Message Block: XML file error: Squitter avel: 'ias_velocity' and 'tas_velocity' are not included!" << endl;
                   return -1;
                 }
             }
             /* ---------- VERTICAL SOURCE ---------- */
             if((t=s->first_node("vertical_source")) != 0)
             {
                //get and check value
                if((sscanf(t->value(),"%ld",&num))!=1 or strpbrk(t->value(),",.") != NULL or num < MIN_VS or num > MAX_VS)
                {
                   cerr << "ADS Message Block: XML file error: Squitter avel: 'vertical_source' has wrong format!"
                        << "(type: integer, range: ["<< MIN_VS <<","<< MAX_VS <<"])" << endl;
                   return -1;
                }
                binary=bitset<1>(num).to_string();
                //store binary representation into avel buffer
                strcat(avelbuf,binary.c_str());
             }
             else
             {
                cerr << "ADS Message Block: XML file error: Squitter avel: 'vertical_source' is not included!" << endl;
                return -1;
             }
             /* ---------- VERTICAL RATE (DOWN) ---------- */
             if((t=s->first_node("down_vertical")) != 0)
             {
                    //get and check value
                if((sscanf(t->value(),"%ld",&num))!=1 or strpbrk(t->value(),",.") != NULL or num < MIN_VER or num > MAX_VER)
                {
                   cerr << "ADS Message Block: XML file error: Squitter avel: 'down_vertical' has wrong format!"
                        << "(type: integer, range: ["<< MIN_VER <<","<< MAX_VER <<"])" << endl;
                   return -1;
                }
                //set vertical sign (down)
                binary=bitset<1>(1).to_string();
                //store binary representation into avel buffer
                strcat(avelbuf,binary.c_str());
                num=(long int)round((fnum/(float)64)+1);
                binary=bitset<9>(num).to_string();
                //store binary representation into avel buffer
                strcat(avelbuf,binary.c_str());
             }
             /* ---------- VERTICAL RATE (UP) ---------- */
             else if((t=s->first_node("up_vertical")) != 0)
             {
                //get and check value
                if((sscanf(t->value(),"%ld",&num))!=1 or strpbrk(t->value(),",.") != NULL or num < MIN_VER or num > MAX_VER)
                {
                   cerr << "ADS Message Block: XML file error: Squitter avel: 'up_vertical' has wrong format!"
                        << "(type: integer, range: ["<< MIN_VER <<","<< MAX_VER <<"])" << endl;
                   return -1;
                }
                //set vertical sign (up)
                binary=bitset<1>(0).to_string();
                //store binary representation into avel buffer
                strcat(avelbuf,binary.c_str());
                num=(long int)round((num/(float)64)+1);
                binary=bitset<9>(num).to_string();
                //store binary representation into avel buffer
                strcat(avelbuf,binary.c_str());
             }
             //no vertical information included
             else
             {
                cerr << "ADS Message Block: XML file error: Squitter avel: 'up_vertical' and 'down_vertical' are not included!" << endl;
                return -1;
             }
             
              /* ---------- TURN ---------- */
              if((t=s->first_node("turn")) != 0)
              {
                 //get and check value
                 if((sscanf(t->value(),"%ld",&num))!=1 or strpbrk(t->value(),",.") != NULL or num < MIN_TU or num > MAX_TU)
                 {
                   cerr << "ADS Message Block: XML file error: Squitter avel: 'turn' has wrong format!"
                        << "(type: integer, range: ["<< MIN_TU <<","<< MAX_TU <<"])" << endl;
                   return -1;
                 }
                 binary=bitset<2>(num).to_string();
                 //store binary representation into avel buffer
                 strcat(avelbuf,binary.c_str());
              }
              else
              {
                 cerr << "ADS Message Block: XML file error: Squitter avel: 'turn' is not included!" << endl;
                 return -1;
              }
              /* ---------- HEIGHT DIFFERENCE ---------- */
              if((t=s->first_node("height_diff")) != 0)
              {
                 //get and check value
                 if((sscanf(t->value(),"%ld",&num))!=1 or strpbrk(t->value(),",.") != NULL or num < MIN_HD or num > MAX_HD)
                 {
                   cerr << "ADS Message Block: XML file error: Squitter avel: 'height_diff' has wrong format!"
                        << "(type: integer, range: ["<< MIN_HD <<","<< MAX_HD <<"])" << endl;
                   return -1;
                 }
                 //signed value
                 if(num<0)
                 {
                   //set sign bit to 1
                   binary=bitset<1>(1).to_string();
                   strcat(avelbuf,binary.c_str());
                   //correct value
                   num=(long int) num*(-1);
                 }
                 if(num>=0)
                 {
                   //set sign bit to 0
                   binary=bitset<1>(0).to_string();
                   strcat(avelbuf,binary.c_str());
                 }
                 binary=bitset<7>(num).to_string();
                 //store binary representation into avel buffer
                 strcat(avelbuf,binary.c_str());
              }
              else
              {
                 cerr << "ADS Message Block: XML file error: Squitter avel: 'height_diff' is not included!" << endl;
                 return -1;
              }
           }
           else
           {
              return 1;
           }
       return 0;
    }
    
    
    int packaging_impl::aid_coding(char* aidbuf,xml_node<> * r_node, int aid_size)
    {
        if((MSG_LEN+1)!=aid_size)
        {
          cerr << "ADS Message Block: Aid coding function: parameters are inconsistent!"<<endl;
          return -1;
        }
        
        xml_node<> * t;   //temporary node
        xml_node<> * s;   //sub node
        string binary;
        char callsign[MAX_CS_LEN]={0};
        long int num=(long int)0;
        
        //clear destination buffers
        memset(aidbuf,0,aid_size);
        
           /* ---------- SQUITTER AIRCRAFT VELOCITY SUBNODE ---------- */
           if((s=r_node->first_node("squitter_aid")) != 0)
           {
              /* ---------- FORMAT TYPE ---------- */
              if((t=s->first_node("format_type")) != 0)
              {
                 //get and check value
                 if((sscanf(t->value(),"%ld",&num))!=1 or strpbrk(t->value(),",.") != NULL or num < MIN_IDF or num > MAX_IDF)
                 {
                   cerr << "ADS Message Block: XML file error: Squitter aid: 'format_type' has wrong format!"
                        << "(type: integer, range: ["<< MIN_IDF <<","<< MAX_IDF <<"])" << endl;
                   return -1;
                 }
                 binary=bitset<5>(num).to_string();
                 //store binary representation into avel buffer
                 strcat(aidbuf,binary.c_str());
              }
              else
              {
                 cerr << "ADS Message Block: XML file error: Squitter aid: 'format_type' is not included!" << endl;
                 return -1;
              }
              
              /* ---------- AIRCRAFT CATEGORY ---------- */
              if((t=s->first_node("category")) != 0)
              {
                 //get and check value
                 if((sscanf(t->value(),"%ld",&num))!=1 or strpbrk(t->value(),",.") != NULL or num < MIN_CAT or num > MAX_CAT)
                 {
                   cerr << "ADS Message Block: XML file error: Squitter aid: 'category' has wrong format!"
                        << "(type: integer, range: ["<< MIN_CAT <<","<< MAX_CAT <<"])" << endl;
                   return -1;
                 }
                 binary=bitset<3>(num).to_string();
                 //store binary representation into avel buffer
                 strcat(aidbuf,binary.c_str());
              }
              else
              {
                 cerr << "ADS Message Block: XML file error: Squitter aid: 'category' is not included!" << endl;
                 return -1;
              }
              
              /* ---------- CALLSIGN CHARACTER ---------- */
              if((t=s->first_node("callsign")) != 0)
              {
                 //get and check value
                 if(strlen(t->value()) < MIN_CS_LEN or strlen(t->value()) > MAX_CS_LEN or strpbrk(t->value()," /.~+-'`´*#:")!=NULL)
                 {
                    cerr << "ADS Message Block: XML file error: Squitter aid: 'callsign' has wrong format!"<<endl;
                    cerr<< "(type: string, min. length: 3 characters / max. length: 8 characters, no whitespace characters allowed)"<<endl;
                    cerr<<"allowed characters: 'A-Z','0-9','_'"<<endl;
                    return -1;
                 }
                 strcpy(callsign,t->value());
                 //if callsign from XML file is shorter than max. length, add characters to callsign
                 if(strlen(callsign)<MAX_CS_LEN)
                 {
                    for(int i=strlen(callsign); i<MAX_CS_LEN;i++)
                    {
                       callsign[i]='_';
                    }
                 }
                 //get callsign value for each character from look-up table
                 for(int i=0; i<MAX_CS_LEN;i++)
                 {
                     if((num=(long int)callsign_value(callsign[i]))==-1 or callsign[i]==' ')
                     {
                         cerr << "ADS Message Block: XML file error: Squitter aid: AID character '"<<callsign[i]
                              <<"'"<<" in 'callsign' is invalid!"<<endl;;
                         return -1;
                     }
                     binary = std::bitset<6>(num).to_string();
                     strcat(aidbuf,binary.c_str());
                 }
              }
              else
              {
                 cerr << "ADS Message Block: XML file error: Squitter aid: 'category' is not included!" << endl;
                 return -1;
              }
           }
           else
           {
              return 1;
           }
        
       return 0;
    }
    
    
    long int packaging_impl::cpr_lat(float lat,int oe,float *rlat)
    {
       float dlati=(float)0;
       const float scale=(float)131072; //2^17 (17 bits)
       float deg=(float)360;
       float z=(float)0;
       float yzi=(float)0;
       long int cpr=0;
       //correct negative values
       if(lat<0)
       {
         lat=(float)(lat+(float)360);
       }
       //even message
       if(oe==0)
       {
          dlati=(float)(deg/60); //size of an even latitude zone
       }
       //odd message
       else if(oe==1)
       {
          dlati=(float)(deg/59); //size of an odd latitude zone
       }
       else
       {
          return -1;
       }
       //mod operation
       z=(float)mod(lat,dlati);
       //calculate latitude value
       yzi=(float)floor((scale*(z/dlati))+0.5);
       //receiver latitude
       *rlat=(float)dlati*(floor(lat/dlati)+(yzi/scale));
       //coded latitude
       cpr=(long int)mod(yzi,scale);
       return cpr;
    }
    
    long int packaging_impl::cpr_lon(float lon,int oe,float *tr,float rlat)
    {
        float dloni=(float)0;
        const float scale=(float)131072; //2^17 (17 bits)
        float z=(float)0;
        float m=(float)0;
        float xyi=(float)0;
        long int cpr=0;
        //correct negative values
        if(lon<0)
        {
          lon=(float)(lon+(float)360);
        }
        if(oe==0) //even
        {
          m=(float)max(1,NL(rlat,&tr[0]));
        }
        else if(oe==1) //odd
        {
          m=(float)max(1,NL(rlat,&tr[0])-1);
        }
        else
        {
          return -1;
        }
        //size of a longitude zone
        dloni=(float)(360/m);
        //mod operation
        z=(float)mod(lon,dloni);
        //calculate longitude value
        xyi=(float)floor((scale*(z/dloni))+0.5);
        //coded longitude
        cpr=(long int)mod(xyi,scale);
        
        return cpr;
    }
    
    
    int packaging_impl:: callsign_value(char str)
    {
          //look-up table
          char csign_table[]="#ABCDEFGHIJKLMNOPQRSTUVWXYZ#####_###############0123456789";
          
          //get the position of characters in the look-up table 
          for(int i=0; i<strlen(csign_table);i++)
          {
             if(str==csign_table[i])
             {
                return i;
             }
          }
          return -1;
    }
    //functions necessary for the calculation
    float packaging_impl::mod(float x,float y)
    {
       return (float)(x-(y*floor(x/y)));
    }
    
    int packaging_impl::NL(float lat, float *tr)
    {
      if(lat==0)
      {
        return 59;
      }
      else if(fabs(lat)>87)
      {
         return 1;
      }
      else if(fabs(lat)<87)
      {
         //get values from look-up table
         for(int i=0; i<TR_ELEMENTS; i++)
         {
             if(fabs(lat)>tr[i])
             {
               return i+1;
             }
         }
      }
      else
      {
        return 2;
      }
      return -1;
    }
    
    void packaging_impl::transition(float *tr)
    {
       float x=(float)0;
       float y=(float)0;
       x=(float)((float)1-cos(M_PI/30));
       for(int i=0; i<TR_ELEMENTS;i++)
       {
         y=(float)((float)1-cos(2*M_PI/(i+2)));
         tr[i]=(float)((float)180/M_PI)*acos(sqrt(x/y));
       }
    }

  } /* namespace xml_decoder */
} /* namespace gr */

