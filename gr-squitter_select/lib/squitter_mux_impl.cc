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
#include "squitter_mux_impl.h"

       unsigned char apos_odd[P_LEN];
       unsigned char apos_even[P_LEN];
       unsigned char gpos_odd[P_LEN];
       unsigned char gpos_even[P_LEN];
       unsigned char avel[P_LEN];
       unsigned char aid[P_LEN];

namespace gr {
  namespace squitter_select {

    squitter_mux::sptr
    squitter_mux::make(const std::string lengthname)
    {
      return gnuradio::get_initial_sptr
        (new squitter_mux_impl(lengthname));
    }

    /*
     * The private constructor
     */
    squitter_mux_impl::squitter_mux_impl(const std::string lengthname)
      : gr::tagged_stream_block("squitter mux",
              gr::io_signature::make(1,1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(char)), lengthname)
    {
      set_tag_propagation_policy(TPP_DONT);
    }

    /*
     * Our virtual destructor.
     */
    squitter_mux_impl::~squitter_mux_impl()
    {
    }

    int
    squitter_mux_impl::calculate_output_stream_length(const gr_vector_int &ninput_items)
    {
      int noutput_items = P_LEN;
      return noutput_items ;
    }

    int
    squitter_mux_impl::work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        message_port_register_in(pmt::mp("set_time"));
        set_msg_handler(pmt::mp("set_time"),boost::bind(&squitter_mux_impl::set_time, this, _1));
        
        const unsigned char *in_d = (const unsigned char *) input_items[0];
        char *out = (char *) output_items[0];
        static int cnt=0;
        int packet_length = ninput_items[0];
       
        cnt++; 
        
        if(cnt==1)
        {
         memcpy((void *)apos_odd, (const void *) in_d, packet_length);
         memcpy((void *)out, (const void *) apos_odd, packet_length);
        }
        if(cnt==2)
        {
         memcpy((void *)apos_even, (const void *) in_d, packet_length);
         memcpy((void *)out, (const void *) apos_even, packet_length);
        }
        if(cnt==3)
        {
         memcpy((void *)gpos_odd, (const void *) in_d, packet_length);
         memcpy((void *)out, (const void *) gpos_odd, packet_length);
        }
        if(cnt==4)
        {
         memcpy((void *)gpos_even, (const void *) in_d, packet_length);
         memcpy((void *)out, (const void *) gpos_even, packet_length);
        }
        if(cnt==5)
        {
         memcpy((void *)avel, (const void *) in_d, packet_length);
         memcpy((void *)out, (const void *)avel, packet_length);
        }
        if(cnt==6)
        {
         memcpy((void *)aid, (const void *) in_d, packet_length);
         memcpy((void *)out, (const void *) aid, packet_length);
        }
        
        

        // Do <+signal processing+>

        // Tell runtime system how many output items we produced.
        return strlen(out);
    }

  } /* namespace squitter_select */
} /* namespace gr */

