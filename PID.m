s = tf('s');
Gs = (0.9789*s+391.4)/(s^2+6.023*(10^-14)*s+200.1) 


kp = 5.333;
ki = 16;
kd = 0.444;


Gc = kp+kd*s+ki/s;

TF = (kp+kd*s+ki/s)*Gs
figure
step(feedback(TF,1))
grid on