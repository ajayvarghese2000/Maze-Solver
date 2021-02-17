clear all
clc
ComPort = 'COM4';
[s,flag] = setupSerial(ComPort);



%tw=readOut(s,1000);
figure;
max_lim = 35000;

while true
    
    
    x=fscanf(s,'%f');
    y=fscanf(s,'%f');
    
    %if rem(a,200)==0
    
    x_fake=[0 max_lim 0 -max_lim];
    y_fake=[max_lim 0 -max_lim 0];
    h_fake=compass(x_fake,y_fake);
    set(h_fake,'Visible','off');
    hold on;
    %}
    compass(x,y)
    hold off;
    %end
    drawnow
end