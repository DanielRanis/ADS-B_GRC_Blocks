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


#ifndef INCLUDED_SQUITTER_SELECT_SQUITTER_MUX_H
#define INCLUDED_SQUITTER_SELECT_SQUITTER_MUX_H

#include <squitter_select/api.h>
#include <gnuradio/tagged_stream_block.h>

namespace gr {
  namespace squitter_select {

    /*!
     * \brief <+description of block+>
     * \ingroup squitter_select
     *
     */
    class SQUITTER_SELECT_API squitter_mux : virtual public gr::tagged_stream_block
    {
     public:
      typedef boost::shared_ptr<squitter_mux> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of squitter_select::squitter_mux.
       *
       * To avoid accidental use of raw pointers, squitter_select::squitter_mux's
       * constructor is in a private implementation
       * class. squitter_select::squitter_mux::make is the public interface for
       * creating new instances.
       */
      static sptr make(const std::string lengthname);
      
      virtual void set_time(pmt::pmt_t msg) = 0;
      
      virtual pmt::pmt_t msg() const = 0;
    };

  } // namespace squitter_select
} // namespace gr

#endif /* INCLUDED_SQUITTER_SELECT_SQUITTER_MUX_H */

