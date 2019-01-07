#!perl
use strict;
use warnings;

use Win32::SerialPort;

$| = 1; #enable autoflush

my $PortName = "COM5";
my $sendData = "Hello World!";

### SERIAL PORT SETUP ###
my $port = new Win32::SerialPort($PortName) or die "$!\n";
$port->initialize();
$port->baudrate(19200);
$port->parity('none');
$port->databits(8);
$port->stopbits(1);
$port->user_msg('ON');
$port->handshake("rts");
$port->write_settings();
sleep(1);
print "DBG: " . $port->baudrate() . "\n";

my $ret = $port->write($sendData);
print $ret;
print "\nOUTPUT:\n";
# while(1) {
#   my $byte=$port->lookfor();
#   if($byte){
#   	print "$byte";
#   } 
#   $port->lookclear;
#   sleep (1);
# }

$port->close();
print "\nDONE\n";
