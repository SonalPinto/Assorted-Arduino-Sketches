scale = 20;

t = 1:128;
A = scale*log2(t);

B = linspace(1,128,17);
% avoid this for linear
B = scale*log2(B);


tt = (0:16)*8;
C = round(A);
C(C>127)=127;
save loglvl.mat C ;


clf
hold on
bar(tt,B);
plot(t, A, "linewidth", 3)
plot(t, t, "linewidth", 3,"color","r")

hold off