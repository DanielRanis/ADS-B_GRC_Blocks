/**
 * @file USB_sink_impl.h
 * @brief This file holds the class declaration of this block.
 * @author Ranisavljevic Daniel
*/


#ifndef INCLUDED_DATA_SINK_USB_SINK_IMPL_H
#define INCLUDED_DATA_SINK_USB_SINK_IMPL_H

//Includes
#include <data_sink/USB_sink.h>
#include <libusb-1.0/libusb.h>
#include <unistd.h>
#include <stdio.h>

//Define
#define MAXLEN 512
#define PCKLEN 64

using namespace std;

namespace gr {
  namespace data_sink {
   
   /**
   * @brief Class of the USB_sink block.
   */
    class USB_sink_impl : public USB_sink
    {
     private:
      int pID;
      int vID;
      float beta;
      bool testUSB;
      int mode;
      int testmsg;

     public:
      //Constructor and Destructor
      USB_sink_impl(const int vendorID, const int productID,bool test);
      ~USB_sink_impl();
      //Function prototypes
      int test_usb_port(void);
      
      int usb_data_transfer(unsigned char *wdata,unsigned char *rdata, int package_length);
      
      int printdev(libusb_device *dev);
      
      int work(int noutput_items,
               gr_vector_const_void_star &input_items,
               gr_vector_void_star &output_items);
      
      char* conv_to_ascii(const char* binstr,int blen);
      
    };
  } // namespace data_sink
} // namespace gr

#endif /* INCLUDED_DATA_SINK_USB_SINK_IMPL_H */

