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
#include "PPM_coding_impl.h"

namespace gr {
  namespace coding {

    PPM_coding::sptr
    PPM_coding::make()
    {
      return gnuradio::get_initial_sptr
        (new PPM_coding_impl());
    }

    /*
     * The private constructor
     */
    PPM_coding_impl::PPM_coding_impl()
      : gr::block("PPM_coding",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(char)))
    {}

    /*
     * Our virtual destructor.
     */
    PPM_coding_impl::~PPM_coding_impl()
    {
    }


    int PPM_coding_impl::general_work (int noutput_items,
                                       gr_vector_int &ninput_items,
                                       gr_vector_const_void_star &input_items,
                                       gr_vector_void_star &output_items)
    {
        const char *in = (const char*) input_items[0];
        char *out = (char*) output_items[0];
        int len=(int)strlen(in);
        char codedstr[(2*len)+1];
        
        if(ppm(&codedstr[0],in,len,(int)sizeof(codedstr))==-1)
        {
           return -1;
        }
        strcpy(out,codedstr);
        
        consume (0,strlen(in));
        // Tell runtime system how many output items we produced.
        return strlen(out);
    }
    
    int PPM_coding_impl::ppm(char* deststr,const char* binstr, int len, int destsize)
    {
       if(len!=strlen(binstr) or (2*len+1)!=destsize)
       {
          cerr << "PPM Coding Block: ppm function: parameters are inconsistent"<<endl;
          return -1;
       }
       static int j=0;

       //clear whole destination buffer
       memset(deststr,0,destsize);
       for(int i=0; i<len;i++)
       {
         if(i==0)
         {
           if(binstr[i]=='0')
           {
             deststr[j++]='0';
             deststr[j++]='1';
           }
           else if(binstr[i]=='1')
           {
             deststr[j++]='1';
             deststr[j++]='0';
           }
         }
         else
         {
           if(binstr[i]=='0')
           {
             deststr[j++]='0';
             deststr[j++]='1';
           }
           else if(binstr[i]=='1')
           {
             deststr[j++]='1';
             deststr[j++]='0';
           }
         }
       }
       deststr[strlen(deststr)]='\0';
       j=0;
      return 0;
    }
  } /* namespace coding */
} /* namespace gr */

