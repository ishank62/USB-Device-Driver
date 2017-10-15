#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>


MODULE_LICENSE("GPL");

//Probe Function
//called on device insertion if and only if no other driver has beat us to the punch
static int pen_probe (struct usb_interface *interface , const struct usb_device_id *id){
	printk(KERN_INFO "[*] Ishank Pen Drive (%04X:%04X) Plugged\n" , id->idVendor , id->idProduct);
	return 0;
}

//disconnect
static void pen_disconnect(struct usb_interface *interface){
	printk(KERN_INFO "[*] Ishank Pen Drive Removed !!\n");
}

//USB Device ID
static struct usb_device_id pen_table[]={
	//0781:5581 
	{ USB_DEVICE(0x0781 , 0x5581 ) },    //Info obtained by using lsusb at command line
	{} //terminating entry
};

MODULE_DEVICE_TABLE(usb , pen_table);

//USB Driver
static struct usb_driver pen_driver={
	.name       = "pen_driver",
	.id_table   = pen_table,     //USB Device ID
	.probe      = pen_probe,
	.disconnect = pen_disconnect,
};

static int __init pen_init(void){
	int ret = -1;
	printk(KERN_INFO "[*] Ishank Contructor Of The Driver");
	printk(KERN_INFO "\t Registering Driver With The Kernel");
	ret = usb_register(&pen_driver);
	printk(KERN_INFO "\t Registration Is Complete !!");
	return ret;
}

static void __exit pen_exit(void){
	//Deregister
	printk(KERN_INFO "[*] Ishank Destructor of the driver");
	usb_deregister(&pen_driver);
	printk(KERN_INFO "\t Unregistration Is Complete !!");
}

module_init(pen_init);
module_exit(pen_exit);

