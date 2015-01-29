/*
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 * 
 * License: MIT
 */

/*
 * Return the first codepoint that falls within the given block.
 */
a_cp a_block_start(int block)
{
    assert(block >= 0 && block < A_MAX_BLOCKS);
    return a_block_ranges[block * 2];
}
/*
 * Return the last codepoint that falls within the given block.
 */
a_cp a_block_end(int block)
{
    assert(block >= 0 && block < A_MAX_BLOCKS);
    return a_block_ranges[block * 2 + 1];
}
/*
 * Return the size of the given block.
 */
a_cp a_block_size(int block)
{
    assert(block >= 0 && block < A_MAX_BLOCKS);
    return a_block_end(block) - a_block_start(block) + 1;
}
/*
 * Convert the block number into a string containing
 * the official name of the block.
 */
const char *a_block_name(int block)
{
    assert(block >= 0 && block < A_MAX_BLOCKS);
    return a_blocks_names[block];
}
/*
 * Obtain the block name of the block in which the codepoint
 * specified is in.
 */
const char *a_block_name_cp(a_cp codepoint)
{
    assert(A_MIN_CP <= codepoint && codepoint <= A_MAX_CP);
    return a_blocks_names[a_block_cp(codepoint)];
}
/*
 * Returns the block in which the given codepoint blongs to. 
 * 
 */
int a_block_cp(a_cp codepoint)
{
    int block;
    assert(A_MIN_CP <= codepoint && codepoint <= A_MAX_CP);
    
    /* Just iterate over the blocks, there are only ~250something
     * blocks, so this shouldn't be too much of a performance hit.
     * we can always switch to a 2-stage table or something should
     * it prove to cause issues. */
    for (block = 0; block < A_MAX_BLOCKS; ++block)
        if (a_block_start(block) <= codepoint && codepoint <= a_block_end(block))
            return block;
    
    /* we should never get here */
    return -1;
}