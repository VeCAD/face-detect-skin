module median_linebuf(clk,datavalid,line_in,line_out);

parameter line_length=640-1;

input clk,datavalid;
input line_in;
output line_out;

integer i;
reg R[0:line_length-1];
always@(posedge clk)
	if(datavalid)begin
		R[0]<=line_in;
		for(i=1;i<line_length;i=i+1)
			R[i]<=R[i-1];
	end

assign line_out=R[line_length-1];

endmodule
