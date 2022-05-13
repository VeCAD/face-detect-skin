module latency_counter(rst,clk,datavalid_in,lat_end);
parameter latency=641;
parameter lat_bit=10;

input rst,clk,datavalid_in;
output lat_end;

reg [lat_bit-1:0]lat_reg;

assign lat_end=(lat_reg==latency);
always@(posedge clk or posedge rst)
	if(rst)
		lat_reg<=0;
	else begin
		if(datavalid_in&~(lat_end))
			lat_reg<=lat_reg+1'd1;
	end
endmodule
