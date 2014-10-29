A=imread('~/metodos/Algo3-Orga2/Tp3/images/img12.bmp');

n=size(A,1)
m=size(A,2)
for i=1:n
    if rem(i,2)==0
        for j=1:m/2
            A(i,j*2-1,2)=0;
            A(i,j*2-1,3)=0;

            A(i,j*2,1)=0;
            A(i,j*2,3)=0;
        end
    else
        for j=1:m/2
            A(i,j*2-1,1)=0;
            A(i,j*2-1,3)=0;
        
            A(i,j*2,1)=0;
            A(i,j*2,2)=0;
        end
    end
end

imwrite(A,'~/metodos/Algo3-Orga2/Tp3/images/img12b.bmp')