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

#ifndef INCLUDED_CONTROL_MODECONTROL_IMPL_H
#define INCLUDED_CONTROL_MODECONTROL_IMPL_H

#include <control/modecontrol.h>

namespace gr {
  namespace control {

    class modecontrol_impl : public modecontrol
    {
     private:
        int mode;
        int tmsg;

     public:
      modecontrol_impl(int mod, int testmsg);
      ~modecontrol_impl();

      int general_work(int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items);
    };

  } // namespace control
} // namespace gr

#endif /* INCLUDED_CONTROL_MODECONTROL_IMPL_H */

