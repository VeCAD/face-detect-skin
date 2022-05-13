`include "median_linebuf.v" 
`include "median_window.sv" 


module median(clk,rst,datavalid,pix_in,datavalid_out,pix_out,pix_ori,grey_in,grey_out,x,y);
input [7:0]grey_in;
output [7:0]grey_out;
///////user defined parameters
parameter imwidth='d800;//'d640;
parameter imheight='d600;//'d480;
parameter m=7;	//window m x n
parameter n=7;

///////auto generated parameters
function integer log2;
      input integer number;
		begin	
         log2=0;	
         while(number>0) 
			begin	
				number=number>>1;
            log2=log2+1;	
         end	
      end	
 endfunction // log2
parameter x_bit=log2(imwidth);
parameter y_bit=log2(imheight);
parameter acc_bit=log2(m*n);
parameter latency=imwidth*(n-1)/2+(m-1)/2;
parameter lat_bit=log2(latency);
////////end of parameter declaration


input rst,clk,datavalid;
input pix_in;
output reg datavalid_out;
output pix_out,pix_ori;

genvar k;

//////window
wire W[0:m-1][0:n-1];
wire W_in[0:n-1];
wire W_out[0:n-1];
assign W_in[0]=pix_in;
median_window #(.m(m),.n(n))
	MW(clk,rst,datavalid,W_in,W,W_out);

/////line buffer
generate
	for(k=1;k<n;k=k+1)begin:line_all
		median_linebuf #(.line_length(imwidth-m))
			MLB(clk,datavalid,W_out[k-1],W_in[k]);
	end
endgenerate

/////coordinate and latency counter
wire lat_end,EOX,EOY;
output [x_bit:0]x;
output [y_bit:0]y;
latency_counter #(.latency(latency),.lat_bit(lat_bit))
	LC(rst,clk,datavalid,lat_end);
xy_counter #(.imwidth(imwidth),.imheight(imheight),.x_bit(x_bit),.y_bit(y_bit))
	XY(rst,clk,datavalid,lat_end,x,y,EOX,EOY);

/////datavalid_out	
always@(posedge clk or posedge rst)
	if(rst)begin
		datavalid_out<=0;
	end
	else if(lat_end)begin
		datavalid_out<=datavalid;
	end
	
////////pix_out
integer j;
wire [acc_bit-1:0]sum;
reg [acc_bit-1:0]sumr,suml,acc;
assign pix_ori=W[(m-1)/2][(n-1)/2];

always@*begin
	sumr=0;suml=0;
	for(j=0;j<n;j++)begin
		sumr=sumr+W[0][j];
		suml=suml+W[m-1][j];
	end
end
assign sum=acc+sumr-suml;
always@(posedge clk or posedge rst)
	if(rst)
		acc<=0;
	else if(datavalid)
		acc<=sum;

////////image border skipping
always @*
	if((x<(m-1)/2)|(x>imwidth-1-(m-1)/2)|(y<(n-1)/2)|(y>imheight-1-(n-1)/2))begin
		pix_out=0;
	end
	else begin
		pix_out=sum>((m*n)>>1);
	end

/////////displaying purpose
reg [7:0]grey_line[0:latency];
always@(posedge clk)
	if(datavalid)begin
		grey_line[0]<=grey_in;
		for(j=1;j<latency+1;j=j+1)
			grey_line[j]<=grey_line[j-1];
	end
assign grey_out=grey_line[latency];

	
endmodule
