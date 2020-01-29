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

#ifndef INCLUDED_CODING_PPM_CODING_IMPL_H
#define INCLUDED_CODING_PPM_CODING_IMPL_H

#include <coding/PPM_coding.h>
#include <string.h>

using namespace std;
namespace gr {
  namespace coding {

    class PPM_coding_impl : public PPM_coding
    {
     private:
      // Nothing to declare in this block.

     public:
      PPM_coding_impl();
      ~PPM_coding_impl();


      int ppm(char* deststr,const char* binstr, int len, int destsize);

      int general_work(int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items);
    };

  } // namespace coding
} // namespace gr

#endif /* INCLUDED_CODING_PPM_CODING_IMPL_H */

