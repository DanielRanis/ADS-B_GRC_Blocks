/* -*- c++ -*- */
/* 
 * Copyright 2018 <+YOU OR YOUR COMPANY+>.
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
#include "modecontrol_impl.h"
#include <string.h>

namespace gr {
  namespace control {

    modecontrol::sptr
    modecontrol::make(int mod, int testmsg)
    {
      return gnuradio::get_initial_sptr
        (new modecontrol_impl(mod,testmsg));
    }

    /*
     * The private constructor
     */
    modecontrol_impl::modecontrol_impl(int mod, int testmsg)
      : gr::block("modecontrol",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(char))),
              mode(mod),
              tmsg(testmsg)
    {}

    /*
     * Our virtual destructor.
     */
    modecontrol_impl::~modecontrol_impl()
    {
    }


    int
    modecontrol_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const char *in = (const char *) input_items[0];
        char*out = (char *)output_items[0];
        
        
        // Tell runtime system how many output items we produced.
        if(mode==1)
        {
          strcpy(out,"1TEST");
        }
        else if(mode==0)
        {
          strcpy(out,"0STOP");
        }
        else
        {
          return -1;
        }
        
        consume(0,strlen(in));
        return strlen(out);
    }

  } /* namespace control */
} /* namespace gr */

