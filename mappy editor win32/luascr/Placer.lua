-- Example smooth edges Placer script
-- called when the mouse moves and a button pressed that is set to Placer.lua
-- Stretch the Block Window so the blocks are aligned as detailed in the
-- Auto smooth guide in the docs

edgetab = {
0, 0, 1, 1, 0, 0, 1, 1, -1, -1, 0, 0, -1, -1, 0, 0
}
invcorners = {
2, 3, 3, 2
}
rowlimits = {
-1, 3, -1, 3, -1, 3
}
towrite = {
0, 0, 0, 0, 0, 0, 0, 0, 0
}

function outlimit (blknum)
 if (blknum < 0) then return -1 end
 if (blknum < rowlimits[1] or (blknum > rowlimits[2] and blknum < rowlimits[3])) then return -1 end
 if ((blknum > rowlimits[4] and blknum < rowlimits[5])) then return -1 end
 if (blknum > rowlimits[6]) then return -1 end
 return 0
end

function edges (bx, by, blk)
 local edgenum = 0
 if outlimit(mappy.getBlock (bx, by-1)) == -1 then edgenum = edgenum + 1 end
 if outlimit(mappy.getBlock (bx+1, by)) == -1 then edgenum = edgenum + 2 end
 if outlimit(mappy.getBlock (bx, by+1)) == -1 then edgenum = edgenum + 4 end
 if outlimit(mappy.getBlock (bx-1, by)) == -1 then edgenum = edgenum + 8 end

-- sort inverse corners
if edgetab[edgenum+1] == 0 then
  if outlimit(mappy.getBlock (bx+1, by+1)) == -1 then return invcorners[1] end
  if outlimit(mappy.getBlock (bx-1, by+1)) == -1 then return invcorners[2] end
  if outlimit(mappy.getBlock (bx-1, by-1)) == -1 then return invcorners[3] end
  if outlimit(mappy.getBlock (bx+1, by-1)) == -1 then return invcorners[4] end
end

return edgetab[edgenum+1]
end

function main ()
-- mappy.BLOCKSPERROW added in V1.4.22, if using with an earlier version, set
--blocksperrow = 20
-- or correct value for your graphics
blocksperrow = mappy.getValue (mappy.BLOCKSPERROW)
if blocksperrow < 5 then blocksperrow = 20 end

local x = mappy.getValue (mappy.MOUSEBLOCKX)
local y = mappy.getValue (mappy.MOUSEBLOCKY)

local blk = mappy.getValue (mappy.CURANIM)
if (blk == -1) then
  blk = mappy.getValue (mappy.CURBLOCK)
else
-- setBlock need anims in the format below (ie: anim 1 should be a value of -2)
  blk = -(blk+1)
end

-- correct edgetab, invcorners and rowlimits
edgetab[2] = edgetab[2] - blocksperrow
edgetab[4] = edgetab[4] - blocksperrow
edgetab[5] = edgetab[5] + blocksperrow
edgetab[7] = edgetab[7] + blocksperrow
edgetab[10] = edgetab[10] - blocksperrow
edgetab[12] = edgetab[12] - blocksperrow
edgetab[13] = edgetab[13] + blocksperrow
edgetab[15] = edgetab[15] + blocksperrow
invcorners[1] = invcorners[1] - blocksperrow
invcorners[2] = invcorners[2] - blocksperrow
rowlimits[1] = (rowlimits[1] - blocksperrow) + blk
rowlimits[2] = (rowlimits[2] - blocksperrow) + blk
rowlimits[3] = (rowlimits[3]) + blk
rowlimits[4] = (rowlimits[4]) + blk
rowlimits[5] = (rowlimits[5] + blocksperrow) + blk
rowlimits[6] = (rowlimits[6] + blocksperrow) + blk

-- Place a '+' of blocks at current position
towrite[5] = blk
mappy.setBlock (x-1, y-1, blk)
mappy.setBlock (x, y-1, blk)
mappy.setBlock (x+1, y-1, blk)
mappy.setBlock (x-1, y, blk)
mappy.setBlock (x, y, blk)
mappy.setBlock (x+1, y, blk)
mappy.setBlock (x-1, y+1, blk)
mappy.setBlock (x, y+1, blk)
mappy.setBlock (x+1, y+1, blk)

-- sort edges before writing
towrite[1] = edges (x-1, y-1, blk)
towrite[2] = edges (x, y-1, blk)
towrite[3] = edges (x+1, y-1, blk)
towrite[4] = edges (x-1, y, blk)
towrite[6] = edges (x+1, y, blk)
towrite[7] = edges (x-1, y+1, blk)
towrite[8] = edges (x, y+1, blk)
towrite[9] = edges (x+1, y+1, blk)

-- write edges
mappy.setBlock (x-1, y-1, blk+towrite[1])
mappy.setBlock (x, y-1, blk+towrite[2])
mappy.setBlock (x+1, y-1, blk+towrite[3])
mappy.setBlock (x-1, y, blk+towrite[4])
mappy.setBlock (x+1, y, blk+towrite[6])
mappy.setBlock (x-1, y+1, blk+towrite[7])
mappy.setBlock (x, y+1, blk+towrite[8])
mappy.setBlock (x+1, y+1, blk+towrite[9])
end

test, errormsg = pcall( main )
if not test then
    mappy.msgBox("Error ...", errormsg, mappy.MMB_OK, mappy.MMB_ICONEXCLAMATION)
end
