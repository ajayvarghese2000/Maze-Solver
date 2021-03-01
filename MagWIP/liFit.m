% Li's ellipsoid specific fitting algorithm:
function v=liFit(S)
    % Create constraint matrix C:
    k=4;

    C(1,:)=[-1,((k/2)-1),((k/2)-1),0,0,0];
    C(2,:)=[((k/2)-1),-1,((k/2)-1),0,0,0];
    C(3,:)=[((k/2)-1),((k/2)-1),-1,0,0,0];
    C(4,:)=[0,0,0,-k,0,0];
    C(5,:)=[0,0,0,0,-k,0];
    C(6,:)=[0,0,0,0,0,-k];
    
    % Solve generalized eigensystem
    S11=S(1:6, 1:6);  S12=S(1:6, 7:10);
    S22=S(7:10,7:10);
    A=S11-S12*pinv(S22)*S12';
    %[gevec, geval]=eig(A, C);

    CA=inv(C)*A;
    [gevec, geval]=eig(CA);
    % Find the largest eigenvalue(the only positive eigenvalue)
    In=1;
    maxVal=geval(1,1);
    for i=2:6
      if (geval(i,i)>maxVal)
          maxVal=geval(i,i);
          In=i;
      end
    end
    % Find the fitting
    v1=gevec(:, In); 
    v2=-pinv(S22)*S12'*v1;
    v=[v1; v2];