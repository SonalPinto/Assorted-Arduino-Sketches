n = 32;
N = [0:n-1];

% cosine and sine components
% Each k in the Spectral domain denotes a single frequency of cosine/sine was used
% the magnitude denotes the effect of that kth frequency in the input
% correllation

% Coefficients - +-127 (8 bit signed)
ReX_coeff = zeros( n/2 , n );
ImX_coeff = zeros( n/2 , n );

scale=1;

for k = 0:(n/2)
	ReX_coeff(k+1,:) = scale * cos(2*pi*k*N / n);
	ImX_coeff(k+1,:) = scale * sin(2*pi*k*N / n);
	k
end

% k=4;
% clf;
% hold on;
% plot (M,ImX_coeff_plot(k,:),'r');
% stem(N,ImX_coeff(k,:));
% hold off;

% sampled signals are here
% N points sampled - can be anything. But then you'll run DFT on N points each time
% max amplitude of pretend signal should be +-127 = 8 bits (coz thats what we constrained in the DFT coeff)
FS = 3200;

t = 1:n;
x1 = 1 * sin(2*pi*400*t / FS);
x2 = 0.5 * sin((2*pi*600*t / FS)  +  pi/3);
x3 = 0.25 * cos((2*pi*800*t / FS ));

x = x1 + x2 + x3;
% x = x-min(x);
x = x/max(abs(x));
%tx = floor (x * scale);
tx = x;
% DFT
ReX = zeros(1,n/2);
ImX = zeros(1,n/2);

for k = 0:(n/2)
	ReX(k+1) = sum ( ReX_coeff(k+1,:) .* tx);
	ImX(k+1) = -1 * sum ( ImX_coeff(k+1,:) .* tx);
end

ReX /= scale * n/2;
ImX /= -1 * scale *  n/2;
ReX(1) /=2;
ReX(n/2) /= 2;

% Inverse DFT
y = zeros(1,n-1);
k = 0:n/2;
for ii = 0:n-1
		y(ii+1) = sum(ReX .* cos(2*pi*ii* k / n)) +  sum(ImX .* sin(2*pi*ii* k / n)) ;
end


dftX = sqrt( ReX.^2 + ImX.^2);
%dftX(dftX<1e-4) = 0; %pretty graph - Magnitude of DFT

% log graph
log_dftX = dftX*128;
log_dftX(log_dftX<1e-4)=1;
log_dftX = 10 * log2 (log_dftX);
log_dftX(log_dftX<1) = 0;

% log2 graph
% 18 scale if 128
% 32 scale if 256
log2_dftX=dftX*128;
log2_dftX(log2_dftX<1e-4)=1;
log2_dftX = 18 * log2 (log2_dftX);
log2_dftX(log_dftX<1) = 0;

clf;
subplot (3,2,1);
	bar (0:n/2, ReX);
	title("ReX[k]");
subplot (3,2,2);
	bar (0:n/2, ImX);
	title("ImX[k]");
subplot (3,2,3);
	bar (0:n/2, log_dftX,"facecolor", "b");
	title("|X[k]| in log10 dB");
subplot (3,2,4);
	bar (0:n/2, dftX,"facecolor", "r");
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