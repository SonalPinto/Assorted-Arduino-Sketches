#!perl

use warnings;
use strict;

use Math::Trig;
use POSIX;

my $A = 0xFE01;
my $root = 0;
my $divisor = 0;
my $remainder = 0;
my $tdivisor = 0;
my $mask ;

print "\nNUMBER: ".sprintf("%b",$A);
foreach (1..8) {
	print "\n\nLoop $_\n--------";
$mask = 0xC000;
	$mask = $mask & $A;

$mask = $mask>>14;
	print "\nmask: ".sprintf("%b",$mask);
	$remainder += $mask;
	print "\nremainder: ".sprintf("%b",$remainder);

	$root = $root<<1;
	$divisor = $divisor<<1;
	$tdivisor = $divisor;
	$tdivisor++;

	print "\nD: ".sprintf("%b",$divisor)."\tTD: ".sprintf("%b",$tdivisor);
	if($remainder>=$tdivisor){
		$root++;
		$divisor += 2;
		$remainder -= $tdivisor;
		print "\n~took 1~";
	} else {
		print "\n~took 0~";
	}

	$remainder = $remainder<<2;
	$A = $A<<2;


	print "\nroot: ".sprintf("%b",$root);
	#last;

}

print "\n\n";