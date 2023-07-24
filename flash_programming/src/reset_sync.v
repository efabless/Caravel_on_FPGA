module reset_sync(input wire clk, input wire rst_n, output wire rst_sync_n );
reg[1:0] sync;
always @(posedge clk or negedge rst_n) begin
   if(!rst_n) sync <= 2'b0;
   else begin
     sync[0] <= 1'b1;
     sync[1] <= sync[0];
   end
end
assign rst_sync_n = sync[1];
endmodule

