module xy_counter(rst,clk,datavalid_in,lat_end,x,y,EOX,EOY);
parameter imwidth=10'd640;
parameter imheight=10'd480;
parameter x_bit=10;
parameter y_bit=10;

input rst,clk,datavalid_in,lat_end;
output reg [x_bit-1:0]x;
output reg [y_bit-1:0]y;
output EOX,EOY;

wire [x_bit-1:0]xend=imwidth-1'd1;
wire [y_bit-1:0]yend=imheight-1'd1;

assign EOX=(x==xend);
assign EOY=(y==yend);

always@(posedge clk or posedge rst)
	if(rst)begin
		x<=xend;y<=yend;
	end
	else begin
		if(datavalid_in&lat_end)begin
			if(EOX)begin
				x<=0;
				if(EOY)
					y<=0;
				else
					y<=y+1'd1;
			end
			else
				x<=x+1'd1;
		end
	end
endmodule
