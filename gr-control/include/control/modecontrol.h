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


#ifndef INCLUDED_CONTROL_MODECONTROL_H
#define INCLUDED_CONTROL_MODECONTROL_H

#include <control/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace control {

    /*!
     * \brief <+description of block+>
     * \ingroup control
     *
     */
    class CONTROL_API modecontrol : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<modecontrol> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of control::modecontrol.
       *
       * To avoid accidental use of raw pointers, control::modecontrol's
       * constructor is in a private implementation
       * class. control::modecontrol::make is the public interface for
       * creating new instances.
       */
      static sptr make(int mod, int testmsg);
    };

  } // namespace control
} // namespace gr

#endif /* INCLUDED_CONTROL_MODECONTROL_H */

