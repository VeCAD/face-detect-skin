module median_window(clk,rst,datavalid,W_in,W,W_out);
//median filter m*n window
parameter m=5;
parameter n=5;

input clk,rst,datavalid;
input W_in[0:n-1];
output W_out[0:n-1];
output reg W[0:m-1][0:n-1];

integer i,j;
always@(posedge clk or posedge rst)
	if(rst)
		for(j=0;j<n;j=j+1)
			for(i=0;i<m;i=i+1)
				W[i][j]<=0;
	else if(datavalid)begin
		for(j=0;j<n;j=j+1)
			for(i=0;i<m;i=i+1)
				if(i==0)
					W[i][j]<=W_in[j];
				else
					W[i][j]<=W[i-1][j];
	end

always@*
	for(j=0;j<n;j=j+1)
		W_out[j]=W[m-1][j];
		
endmodule
