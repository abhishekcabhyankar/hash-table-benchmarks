#!/usr/bin/env lua

local socket = require("socket")
 
function lookup(m, b, r)
   local sum = 0
   
   local t1 = socket.gettime()
   for i = 1, r do
      local x = m[b[i]]
      if x then
	 sum = sum + x
      end
   end
   local t2 = socket.gettime()
   
   return (t2 - t1) * 1000000
end

function random_input(a, n, b, r)
   for i = 1, n do
      a[i] = math.random(0, 1000000000)
   end
   for i = 1, r do
      if i % 2 == 1
      then
	 b[i] = a[math.random(1, n)]
      else
	 b[i] = math.random(0, 1000000000)
      end
   end
end

function main(arg)
   local n = tonumber(arg[1])
   local r = tonumber(arg[2])
   local k = tonumber(arg[3])
   local m = {}
   local a = {}
   local b = {}

   local t = 0
   for j = 1, k do
      random_input(a, n, b, r)
      for i = 1, n do 
	 m[a[i]] = i
      end
      
      t = t + lookup(m, b, r)
      m = {}
   end

   io.write(string.format("%.2f MOPS\n", (r  * k) / t))
end

main(arg)
