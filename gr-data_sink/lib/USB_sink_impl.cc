/**
 * @file USB_sink_impl.cc
 * @brief This file holds the whole data processing of this block.
 * @author Ranisavljevic Daniel
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

//Includes
#include <gnuradio/io_signature.h>
#include "USB_sink_impl.h"

using namespace std;

namespace gr {
  namespace data_sink {
     
    /**
    * @brief shared_ptr
    */
    USB_sink::sptr
    /**
    * @brief data_sink::USB_sink::make is the public interface for creating new instances.
    */
    USB_sink::make(const int vendorID, const int productID,bool test)
    {
      return gnuradio::get_initial_sptr
        (new USB_sink_impl(vendorID,productID,test));
    }

    
   /**
   * @brief private constructor for sync block
   * @param none
   * @return nothing
   */
    USB_sink_impl::USB_sink_impl(const int vendorID, const int productID, bool test)
      : gr::sync_block("USB_sink",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(0, 0, 0)),
              vID(vendorID),
              pID(productID),
              testUSB(test)
    {}

   /**
   * @brief virtual destructor
   * @param none
   * @return nothing
   */
    USB_sink_impl::~USB_sink_impl()
    {
    }

   /**
   * @brief Work function
   * @param noutput_items: Amount of output items that should be created.
   * @param input_items: Address of input items.
   * @param output_items: Address of output items.
   * @return Amount of output items that were created.
   */
    int USB_sink_impl::work(int noutput_items,
                            gr_vector_const_void_star &input_items,
                            gr_vector_void_star &output_items)
    {
        char *in = (char *) input_items[0];
        //temporary buffer
        unsigned char inBuffer[MAXLEN];
        unsigned char outBuffer[MAXLEN];
        
        //temporary pointer
        char *temp=NULL;
        char *asciistr=NULL;
        char id[1];
        int nbyte=0;
        
        //clear temporary buffer
        memset(inBuffer,0,MAXLEN);
        memset(outBuffer,0,MAXLEN);
        //message identification
        id[0]=(unsigned char)in[0]-48;
        //point to message
        temp=&in[1];
        
        //calculate amount of bytes 
        if(strlen(temp)>0)
        {
          nbyte=(int)round(strlen(temp)/8);
        }
        else
        {
          nbyte=1;
        }
        
        if(testUSB)  //show information of connected USB ports.
        {
           if(test_usb_port()==-1)
           {
              return -1;
           }
        }
        
        else //write to specified USB port.
        {
           //convert to ASCII representation
           if(strlen(temp)>0)
           {
              asciistr=conv_to_ascii(temp,nbyte);
              inBuffer[0]=id[0];
              
              for(int i=0; i<nbyte;i++)
              {
                 inBuffer[i+1]=(unsigned char)asciistr[i];
              }
              
              
              if(usb_data_transfer((unsigned char*)&inBuffer,(unsigned char*)&outBuffer,nbyte+1)==-1)
              {
                return -1;
              }
           }
           else
           {
               
              if(usb_data_transfer((unsigned char*)&id,(unsigned char*)&outBuffer,nbyte)==-1)
              {
                return -1;
              }
           }
           
        }

        return noutput_items;
    }
    
   /**
   * @brief Function that transmits data over the specified USB port.
     (based on the libusb example: 
      http://www.dreamincode.net/forums/topic/148707-introduction-to-using-libusb-10/)
   * @param data: data to transmit
   * @param package_length: data length
   * @return integer value (1 if error occured, 0 if successfull)
   */
    int USB_sink_impl::usb_data_transfer(unsigned char *wdata,unsigned char *rdata, int package_length)
    {
        libusb_device **devs; //list of devices
        libusb_device_handle *dev_handle; //device handler
        libusb_context *ctx = NULL; //libusb session
        int npackets=0;
        int r; //return value
        int actual; //amount of bytes that were written
        ssize_t cnt; //number of devices in list

        r = libusb_init(&ctx); //initialization of the libusb library
        if(r < 0) { //error occured
           cout<<"Init Error "<<r<<endl; 
           return -1;
        }
        
        libusb_set_debug(ctx, 3); //set verbosity level to 3
        
        cnt = libusb_get_device_list(ctx, &devs); //get the list of devices
        if(cnt < 0) { //error occured
           cout<<"Get Device Error"<<endl;
           return -1;
        }
        cout<<cnt<<" devices found"<<endl;
        
        dev_handle = libusb_open_device_with_vid_pid(ctx, vID, pID); //open USB port according to the vendorID and productID
        if(dev_handle == NULL){ //error occured
           cout<<"Cannot open device"<<endl;
           return -1;
        }
        else{
           cout<<"Device Opened"<<endl;
        }
           
        libusb_free_device_list(devs, 1); //free the device list and unref the devices
       
        if(libusb_kernel_driver_active(dev_handle, 0) == 1) { //find out if kernel driver is attached
          cout<<"Kernel Driver Active"<<endl;
          if(libusb_detach_kernel_driver(dev_handle, 0) == 0) {//detach it
            cout<<"Kernel Driver Detached!"<<endl;
          }
        }
        r = libusb_claim_interface(dev_handle, 0); //claim interface 0
        if(r < 0) { //error occured
          cout<<"Cannot Claim Interface"<<endl;
          return -1;
        }
        cout<<"Claimed Interface"<<endl;
        
        //Data transfer
        unsigned char*ptr=NULL;
        ptr=&wdata[0];
        int num=0;
        if(package_length>PCKLEN)
        {
          while(1)
          {
              //Data is written to endpoint 0x1 (out endpoint)
              num++;
              cout<<"Sending packet "<< num <<"..."<<endl;
              r = libusb_bulk_transfer(dev_handle, (0x1 | LIBUSB_ENDPOINT_OUT), ptr, PCKLEN, &actual, 0); //write endpoint is 0x1
              if(r == 0 && actual == PCKLEN){ //write operation successfull
                 cout<<"Packet "<< num <<" sent successfully!"<<endl;
              }
              else{ //error occured
                 cout<<"Write Error"<<endl;
                 break;
              }
             
              //Data is read from endpoint 0x81 (in endpoint)
              cout<<"Waiting on response..."<<endl;
              r = libusb_bulk_transfer(dev_handle, (0x81| LIBUSB_ENDPOINT_IN) , rdata, 1, &actual, 500); //read endpoint is 0x81
              if(r == 0 && actual == 1){ //write operation successfull
                 cout<<"Acknowledge received "<<" for packet " << num <<"!"<<endl;
                 ptr=ptr+PCKLEN;
              }
              else if(r == LIBUSB_ERROR_TIMEOUT)
              {
                 cout<<"Timeout error!"<<endl;
                 break;
              }
              else{ //error occured
                 cout<<"Read Error"<<endl;
                 break;
              }
              
              if(num==3)
              {
                 ptr=&wdata[0];
                 cout<<"All packets sent!"<<endl; 
                 break;
              }
          }
        }
        else
        {
              cout<<"Sending data ..."<<endl;
              r = libusb_bulk_transfer(dev_handle, (0x1 | LIBUSB_ENDPOINT_OUT), wdata, PCKLEN, &actual, 0); //write endpoint is 0x1
              if(r == 0 && actual == PCKLEN){ //write operation successfull
                 cout<<"Data sent successfully!"<<endl;
                 
                 //Data is read from endpoint 0x81 (in endpoint)
                 cout<<"Waiting on response..."<<endl;
                 r = libusb_bulk_transfer(dev_handle, (0x81| LIBUSB_ENDPOINT_IN) , rdata, 1, &actual, 500); //read endpoint is 0x81
                 if(r == 0 && actual == 1){ //write operation successfull
                    cout<<"Acknowledge received!"<<endl;
                 }
                 else if(r == LIBUSB_ERROR_TIMEOUT)
                 {
                    cout<<"Timeout error!"<<endl;
                 }
                 else{ //error occured
                    cout<<"Read Error"<<endl;
                 }
              }
              else{ //error occured
                 cout<<"Write Error"<<endl;
              }

        }

          
        //release interface
        r = libusb_release_interface(dev_handle, 0);
        if(r!=0) { //error occured
          cout<<"Cannot Release Interface"<<endl;
          return -1;
        }
        cout<<"Released Interface"<<endl;
        libusb_close(dev_handle); //close opened device 
        libusb_exit(ctx); //exit session

        return 0;
    }
    
   /**
   * @brief Function that displays information of the connected USB ports.
     (based on the libusb example: 
      http://www.dreamincode.net/forums/topic/148707-introduction-to-using-libusb-10/)
   * @param none
   * @return integer value (1 if error occured, 0 if successfull)
   */
    int USB_sink_impl::test_usb_port(void)
    {
       libusb_device **devs; //list of devices
       libusb_context *ctx = NULL; //libusb session
       int r; //return value
       ssize_t cnt; //number of devices in list
       r = libusb_init(&ctx); //libusb session
       if(r < 0) {
           cout<<"Init Error"<<r<<endl; //error occured
           return -1;
       }
       libusb_set_debug(ctx, 3); //set verbosity level to 3
       cnt = libusb_get_device_list(ctx, &devs); //get the list of devices
       if(cnt < 0) {
           cout<<"Get Device Error"<<endl; //error occured
       }
       cout<<cnt<<" Devices in list."<<endl; //diplay total number of usb devices
       ssize_t i; //list iterator variable
       cout <<"********** USB PORT TEST **********" <<endl;
       cout <<"List of USB ports and their configurations:\n" <<endl;
       for(i = 0; i < cnt; i++) {
           cout <<"************* DEVICE "<<i+1<<" *************" <<endl;
           if(printdev(devs[i])==-1) //display information of the device
           {
             return -1;
           }
           cout <<"********** END OF DEVICE "<<i+1<<" **********" <<endl;
       }
       libusb_free_device_list(devs, 1); //free the device list and unref the devices
       libusb_exit(ctx); //exit session
       return 0;
    }

   /**
   * @brief Function that prints out information of a specific USB port.
     (based on the libusb example: 
      http://www.dreamincode.net/forums/topic/148707-introduction-to-using-libusb-10/)
   * @param dev: Pointer to a device list (device from a list).
   * @return nothing
   */
    int USB_sink_impl::printdev(libusb_device *dev)
    {
       libusb_device_descriptor desc; //device descriptor
       int r = libusb_get_device_descriptor(dev, &desc);
       if (r < 0) {
          cout<<"failed to get device descriptor"<<endl;
          return -1;
       }
       cout<<"Number of possible configurations: "<<(int)desc.bNumConfigurations<<"  ";
       cout<<"Device Class: "<<(int)desc.bDeviceClass<<"  ";
       cout<<"VendorID: "<<desc.idVendor<<"  ";
       cout<<"ProductID: "<<desc.idProduct<<endl;
       libusb_config_descriptor *config; // configuration node
       libusb_get_config_descriptor(dev, 0, &config);
       cout<<"Interfaces: "<<(int)config->bNumInterfaces<<" ||| ";
       const libusb_interface *inter;
       const libusb_interface_descriptor *interdesc;
       const libusb_endpoint_descriptor *epdesc;
       for(int i=0; i<(int)config->bNumInterfaces; i++) {
           inter = &config->interface[i];
           cout<<"Number of alternate settings: "<<inter->num_altsetting<<" | ";
           for(int j=0; j<inter->num_altsetting; j++) {
               interdesc = &inter->altsetting[j];
               cout<<"Interface Number: "<<(int)interdesc->bInterfaceNumber<<" | ";
               cout<<"Number of endpoints: "<<(int)interdesc->bNumEndpoints<<" | ";
               for(int k=0; k<(int)interdesc->bNumEndpoints; k++) {
                   epdesc = &interdesc->endpoint[k];
                   cout<<"Descriptor Type: "<<(int)epdesc->bDescriptorType<<" | ";
                   cout<<"EP Address: "<<(int)epdesc->bEndpointAddress<<" | ";
               }
          }
       }
       cout<<endl;
       libusb_free_config_descriptor(config); //free configuarion node
       return 0;
    }
    
    char* USB_sink_impl::conv_to_ascii(const char* binstr,int blen)
    {
       bitset<8> bs;
       //allocate memory for buffer
       char* cdata=(char*)calloc(blen,sizeof(char));
       if(cdata==NULL)
       {
           cerr << "TIVA Block : Error : in function: conv_to_ascii(): Memory allocation" <<endl;
           return NULL;
       }
       istringstream in(binstr); //place into stream
       for(int i=0; i<blen;i++)
       {
         in>>bs;
         cdata[i]=char(bs.to_ulong()); //store ASCII characters
       }
       return cdata;
    }

  } /* namespace data_sink */
} /* namespace gr */






