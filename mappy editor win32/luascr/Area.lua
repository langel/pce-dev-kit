-- Example Area script
-- called when the mouse moves and a button pressed that is set to Area.lua

function main ()
 local x1 = mappy.getValue (mappy.MOUSEBLOCKX)
 local y1 = mappy.getValue (mappy.MOUSEBLOCKY)
 local x2 = mappy.getValue (mappy.MOUSEBLOCKX2)
 local y2 = mappy.getValue (mappy.MOUSEBLOCKY2)

 local blk = mappy.getValue (mappy.CURANIM)
 if (blk == -1) then
  blk = mappy.getValue (mappy.CURBLOCK)
   if (blk == -1) then return end
 else
-- setBlock need anims in the format below (ie: anim 1 should be a value of -2)
  blk = -(blk+1)
 end

 mappy.copyLayer(mappy.getValue(mappy.CURLAYER),mappy.MPY_UNDO)

 if x2 < x1 then
  xtmp = x1
  x1 = x2
  x2 = xtmp
 end

 if y2 < y1 then
  ytmp = y1
  y1 = y2
  y2 = ytmp
 end

 local y = y1
 while y <= y2 do
  local x = x1
  while x <= x2 do
   mappy.setBlock (x, y, blk)
   x = x + 1
  end
  y = y + 1
 end

 mappy.updateScreen()

end

test, errormsg = pcall( main )
if not test then
    mappy.msgBox("Error ...", errormsg, mappy.MMB_OK, mappy.MMB_ICONEXCLAMATION)
end

