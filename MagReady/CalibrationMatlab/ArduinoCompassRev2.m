clear all
clc
if ~isempty(instrfind)
    fclose(instrfind);
    delete(instrfind);
end
close all
clc
disp('Serial port closed')
ComPort = 'COM4';
[s,flag] = setupSerial(ComPort);

%Use this with compassTestArduino
%dont forget to set bias there

figure;
max_lim = 35000;

while true
    
    
    x=fscanf(s,'%f');
    y=fscanf(s,'%f');
    
    xraw=fscanf(s,'%f');
    yraw=fscanf(s,'%f');
    
  
    x_fake=[0 max_lim 0 -max_lim];
    y_fake=[max_lim 0 -max_lim 0];
    h_fake=compass(x_fake,y_fake);
    set(h_fake,'Visible','off');
    hold on;
    view(90,-90)
    %}
    compass(xraw,yraw,'r')%red is raw
    compass(x,y,'b')%blue is calibrated
    hold off;
    %end
    drawnow
end