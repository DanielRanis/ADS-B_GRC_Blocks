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

#ifndef INCLUDED_XML_DECODER_PACKAGING_IMPL_H
#define INCLUDED_XML_DECODER_PACKAGING_IMPL_H

#include <xml_decoder/packaging.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <bitset>
#include <sstream>
#include <unistd.h>
#include <stdlib.h>
#include <wchar.h>

#include "../include/rapidxml-1.13/rapidxml.hpp"
#include "../include/rapidxml-1.13/rapidxml_print.hpp"

#define H_LEN        32
#define MSG_LEN      56
#define FRAME_LEN    528
#define MAX_CS_LEN   8
#define MIN_CS_LEN   3

#define TR_ELEMENTS  58
#define _USE_MATH_DEFINES

//RANGE DEFINES
#define MAX_AC_ADDR 16777215
#define MIN_AC_ADDR 0
#define MAX_CA      7
#define MIN_CA      0
#define MAX_DF      22
#define MIN_DF      9
#define MAX_AF      22
#define MIN_AF      9
#define MAX_IDF     4
#define MIN_IDF     1
#define MAX_CAT     7
#define MIN_CAT     0
#define MAX_VF      19
#define MIN_VF      19
#define MAX_GF      8
#define MIN_GF      5
#define MAX_MV      127
#define MIN_MV      0
#define MAX_ST      1
#define MIN_ST      0
#define MAX_V       1023
#define MIN_V       0
#define MAX_VUNC    7
#define MIN_VUNC    0
#define MAX_VS      1
#define MIN_VS      0
#define MAX_VER     32640.0
#define MIN_VER     0.0
#define MAX_STY     4
#define MIN_STY     1
#define MAX_ICF     1
#define MIN_ICF     0
#define MAX_IFR     1
#define MIN_IFR     0
#define MAX_IAS     1023
#define MIN_IAS     0
#define MAX_TU      3
#define MIN_TU      0
#define MAX_HD      127
#define MIN_HD      -127
#define MAX_TAS     1023
#define MIN_TAS     0
#define MAX_GT      360.0
#define MIN_GT      0.0
#define MAX_DIR     360.0
#define MIN_DIR     0.0
#define MAX_SRV_ST  3
#define MIN_SRV_ST  0
#define MAX_ANT     1
#define MIN_ANT     0
#define MAX_ALT     408500
#define MIN_ALT     0
#define MAX_T_UTC   1
#define MIN_T_UTC   0
#define MAX_LAT     90.0
#define MIN_LAT     -90.0
#define MAX_LON     180.0
#define MIN_LON     -180.0

using namespace rapidxml;
namespace gr {
  namespace xml_decoder {

    class packaging_impl : public packaging
    {
     private:
      int sqttrmode;

     public:
      packaging_impl();
      ~packaging_impl();

      int general_work(int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items);
      
      void forecast (int noutput_items,
                     gr_vector_int &ninput_items_required);
      
      int tag_content(const char *tag,char *buf,float *fval,int *ival,char *sign);
      
      int ppm(char* deststr,const char* binstr, int len, int destsize);
      
      long int cpr_lat(float lat,int oe,float *rlat);
      long int cpr_lon(float lon,int oe,float *tr,float rlat);
            
      int callsign_value(char str);
      
      int header_coding(char* hbuf,xml_node<> * r_node, int header_size);
      int apos_coding(char* aposbuf_even,char* aposbuf_odd,xml_node<> * r_node,float* tr,int apos_even_size, int apos_odd_size);
      int gpos_coding(char* gposbuf_even,char* gposbuf_odd,xml_node<> * r_node,float* tr,int gpos_even_size, int gpos_odd_size);
      int avel_coding(char* avelbuf,xml_node<> * r_node, int avel_size);
      int aid_coding(char* aidbuf,xml_node<> * r_node, int aid_size);
      
      int apos_coding(char* apos_even, char* apos_odd);
      int NL(float lat,float *tr);
      float mod(float x,float y);
      void transition(float *tr);
    };

  } // namespace xml_decoder
} // namespace gr

#endif /* INCLUDED_XML_DECODER_PACKAGING_IMPL_H */

