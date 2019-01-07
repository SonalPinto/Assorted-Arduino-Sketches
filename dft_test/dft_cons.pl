#!perl

use warnings;
use strict;

use Math::Trig;
use POSIX;

# N point DFT
my $N = 32;

# ReX[] constants
# Will store N/2 cosines, sampled over 0-N/2
my @REx_cons=();

# ImX[]
# Will store N/2 sines, sampled over 0-N/2
my @IMx_cons=();

# COEFF GEN - Use code to generate coefficients
# Else use results of that directly, best for simulation
foreach my $k (0..($N/2)) {
	foreach my $i (0..$N-1){
		$REx_cons[$k][$i] =  floor (127 * sprintf("%.5f",cos((2*pi*$i ) * ($k/ $N))));	# cos(2*pi*i*k/N) = particular cosine at kth frequency. 
		$IMx_cons[$k][$i] = floor( -127 * sprintf("%.5f",sin((2*pi*$i) * ($k/ $N))));
	}
}


# print "\n\$REx_cons=(";
# foreach my $k (0..($N/2)){
# 	#print "\n$k :: ";
# 	print "\n{";
# 	foreach my $i (0..$N-1){
# 		print "$REx_cons[$k][$i],";
# 	}
# 	print "},";
# }
# print "\n\$IMx_cons=(";
# foreach my $k (0..($N/2)){
# 	#print "\n$k :: ";
# 	print "\n{";
# 	foreach my $i (0..$N-1){
# 		print "$IMx_cons[$k][$i],";
# 	}
# 	print "},";
# }


# #my @signal = (80,45,15,-1,-30,-57,-48,-14,22,64,88,36,-75,-127,-57,50);
# my @signal = (82,46,16,0,-30,-57,-47,-14,23,65,89,37,-75,
# -128,-57,50,82,46,16,0,-30,-57,-47,-14,23,65,
#  89,37,-75,-128,-57,50);

# # DFT
# my @dft_ReX = ();
# my @dft_ImX = ();

# foreach my $k (0..$N/2) {
# 	$dft_ReX[$k]=0;
# 	$dft_ImX[$k]=0;
# 	foreach my $ii (0..$N-1) {
# 		$dft_ReX[$k] += $REx_cons[$k][$ii] * $signal[$ii];
# 		$dft_ImX[$k] += -1 * $IMx_cons[$k][$ii] * $signal[$ii];
# 	}
# }

# # Magnitude Correction
# foreach my $k (0..$N/2) {
# 	$dft_ReX[$k] /= 128*($N/2);
# 	$dft_ImX[$k] /= 128*($N/2);
# }
# $dft_ReX[0] /=2;
# $dft_ReX[8] /=2;

# # Magnitude calculation
# my @dftX=();
# foreach my $k (0..$N/2){
# 	$dftX[$k] = sqrt($dft_ReX[$k]**2 + $dft_ImX[$k]**2);
# 	$dftX[$k] = floor(sprintf("%.3f",$dftX[$k]))
# }

# print "\n\nDFT:";
# # print "\n@dft_ReX";
# # print "\n@dft_ImX";
# print "\n@dftX";


# Generation of LUT for calculating 18*log2(n)
my @lvl=( 56.878,73.383,83.394,90.602,96.237,100.87,104.79,108.2,
	111.22,113.92,116.36,118.6,120.65,122.56,124.34,127);
# my @lvl = (50,65,74,80,85,89,93,96,98,101,103,105,107,108,110,112);
my $index=0;
my @logMag;
print "\n\nuint8_t logMag[128]={";
foreach my $i (0..127) {
	if($i > $lvl[$index]) {
		$index++;
	}
	$logMag[$i]=$index;
	# print "\n$i     =   $index";
	print ",$index";
}
print "\n};";

print "\n\n";