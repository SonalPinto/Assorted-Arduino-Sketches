
% 64pt DFT
n = 64;
N = [0:n-1];
scale=1;

% Coefficients - +-127 (8 bit signed)
ReX_coeff = zeros( n/2 , n );
ImX_coeff = zeros( n/2 , n );

% Generate all the coefficients
for k = 0:(n/2)
	ReX_coeff(k+1,:) = scale * cos(2*pi*k*N / n);
	ImX_coeff(k+1,:) = scale * sin(2*pi*k*N / n);
end

% Create some input signal to work with
% Keep Sampling Theorem in mind! Nyquist Frequency! 
FS = 17500;

t = 1:n;
x1 = 0.7 * sin(2*pi*6290*t / FS);
x2 =  0.5 * sin((2*pi*48*t / FS)  +  pi/3);
x3 =  0.25 * cos((2*pi*256*t / FS ));
x4 =  0.33 * sin((2*pi*2000*t / FS ));
x5 =  0.4 * sin((2*pi*3200*t / FS ));

x = x1 + x2 + x3 + x4 + x5;
x = x/max(abs(x));

% Windowing - Hamming Window
% Best Guide - http://en.wikipedia.org/wiki/Window_function
% If you don't want a window, just do window = 1, duh...
aa = 0.54;
window = aa - ((1-aa)*cos(2*pi*N/(n-1)));
x = window.*x;
ww = round(window*127);

% Save the window function to built LUT in Arduino Sketch
save window.mat ww; 

% Save input signal for Testing
xx = floor(x*127);
save xx.mat xx;
tx = x;

% DFT - The main course
ReX = zeros(1,n/2);
ImX = zeros(1,n/2);

for k = 0:(n/2)
	ReX(k+1) = sum ( ReX_coeff(k+1,:) .* tx);
	ImX(k+1) = -1 * sum ( ImX_coeff(k+1,:) .* tx);
end

% Correction for Magnitude
ReX /= scale * n/2;
ImX /= -1 * scale *  n/2;
ReX(1) /=2;
ReX(n/2) /= 2;

% Inverse DFT - for fun
y = zeros(1,n-1);
k = 0:n/2;
for ii = 0:n-1
		y(ii+1) = sum(ReX .* cos(2*pi*ii* k / n)) +  sum(ImX .* sin(2*pi*ii* k / n)) ;
end


% This is what we want - The Magnitude Frequency Distribution
dftX = sqrt( ReX.^2 + ImX.^2);

% Get a neat log2 graph
% 18 scale if 128
% 32 scale if 256
log2_dftX=dftX*128;
log2_dftX(log2_dftX<1e-4)=1;
log2_dftX = 18 * log2 (log2_dftX);
log2_dftX(log2_dftX<1) = 0;

% Plot all the cool stuff
clf;
subplot (3,2,1);
	bar (0:n/2, ReX);
	title("ReX[k]");
subplot (3,2,2);
	bar (0:n/2, ImX);
	title("ImX[k]");
subplot (3,2,3:4);
	bar (0:n/2, dftX*128,"facecolor", "r");
	title("|X[k]|");
	set(gca,'XTick',0:2:n/2)
	xt = get(gca,'XTick');
    for ii = 1:length(xt)
        xtl{ii} = sprintf('%.0f', (xt(ii) * (FS/n)));
    end
    set(gca,'XTickLabel',xtl);
subplot (3,2,5);
	bar (0:n/2, log2_dftX,"facecolor", "b");
	title("|X[k]| in log2 dB");
subplot (3,2,6);
	hold on;
	stem (N, tx, "color", "cyan","linewidth",5);
	stem (N, y, "color","red","linewidth",2);
	title("x[n] vs iDFT(X[k])");
	hold off;