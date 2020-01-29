/**
 * @file squitter_output_impl.h
 * @brief This file holds the class declaration of this block.
 * @author Ranisavljevic Daniel
*/


#ifndef INCLUDED_SQUITTER_MUX_SQUITTER_OUTPUT_IMPL_H
#define INCLUDED_SQUITTER_MUX_SQUITTER_OUTPUT_IMPL_H


//Includes
#include <squitter_mux/squitter_output.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "../include/rapidxml-1.13/rapidxml.hpp"
#include "../include/rapidxml-1.13/rapidxml_print.hpp"

#define PRE_LEN      16
#define BUF_LEN      16
//Defines 
#define MAX_SIZE 2
#define CORRFACT 100
//Defines (range)
#define MAX_ALPHA   1.0
#define MIN_ALPHA   0.0
#define MAX_PWIDTH  18
#define MIN_PWIDTH  1
#define MAX_SR    60
#define MIN_SR    1
#define MAX_SPAN    10
#define MIN_SPAN    1
#define MAX_SPS     10
#define MIN_SPS     1
#define MAX_IMX     20
#define MIN_IMX     1
#define MAX_TIME    65535
#define MIN_TIME    1
#define MAX_PRE     65535
#define MIN_PRE     0
#define MAX_TMSG    0xFF
#define MIN_TMSG    0
//Defines (size)
#define ALPHA_SIZE  8
#define PWIDTH_SIZE 8
#define SR_SIZE     8
#define SPAN_SIZE   8
#define SPS_SIZE    8
#define IMX_SIZE    8
#define TINFO_SIZE  8
#define TMSG_SIZE   8

using namespace rapidxml;

namespace gr {
  namespace squitter_mux {

   /**
   * @brief Class of the squitter_output block.
   */
    class squitter_output_impl : public squitter_output
    {
     private:
      float alpha;
      int pw;
      int sr;
      int imx;
      int span;
      int sps;
      int mode;
      int tmsg;

     public:
      //Constructor and Destructor
      squitter_output_impl(const float alpha_param,
                          const int pw_param,
                          const int sr_param,
                          const int span_param,
                          const int sps_param,
                          const int imx_param,
                          const int md,
                          const int testmsg);
      ~squitter_output_impl();
     
      //Function prototypes
      int general_work(int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items);
      
      int preamble_coding(char* pbuf,
                          xml_node<> * r_node,
                          int preamble_size);
      
      int time_coding(char* buf,
                      xml_node<> * r_node,
                      int buf_size,
                      const char* node);
    };

  } // namespace squitter_mux
} // namespace gr

#endif /* INCLUDED_SQUITTER_MUX_SQUITTER_OUTPUT_IMPL_H */

