%Función de transferencia
Gs = tf([-5.428],[1 0.1339 54.1]);

%Controlador Adelanto/atraso
C = zpk([-5.33 -5 -0.01],[-3.74 -0.001],-5.6978);

%Función compensada a lazo cerrado
Gc = feedback(C*Gs,1);

%Respuesta al escalón

step(Gc)