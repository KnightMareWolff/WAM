/************************************************************************************/
/*Project: Whammy Bombs - WAM                                                       */
/*----------------------------------------------------------------------------------*/
/*                                 WAMGameBlock                                     */
/*----------------------------------------------------------------------------------*/
/*Description:                                                                      */
/*The WAMGameBlock Object are responsible for a single position in the map          */
/*the idea behind the block is basically for each position in the 2d map we have a  */
/*box where we can use for many purposes, since for navigation to check pawns etc.. */
/*In future we can create dungeons and check colisions and use the Unreal Map Editor*/
/*to make possible manage the creation of different game maps without change the    */
/*game rules , and many more possibilities(The sky is the limit... ;)               */
/*----------------------------------------------------------------------------------*/
/*Author: William D. Wolff - 2018                                                   */
/************************************************************************************/
#pragma once

#define WAM_BLOCK_TYPE_BLOCK     0
#define WAM_BLOCK_TYPE_FREE      1
#define WAM_BLOCK_TYPE_DESTR     2
#define WAM_BLOCK_TYPE_SPAWN_P1  3
#define WAM_BLOCK_TYPE_SPAWN_P2  4
#define WAM_BLOCK_TYPE_BOMB      5
#define WAM_BLOCK_TYPE_EXPLOSION 6
#define WAM_BLOCK_TYPE_ENEMY     7
#define WAM_BLOCK_TYPE_FLAG      8

/**
 * 
 */
class WAM_API WAMGameBlock
{
public:
	 WAMGameBlock();
	~WAMGameBlock();

	int     iWAM_BlockType;
	int     iWAM_HidenItem;
	bool    iWAM_Impacted;
};
