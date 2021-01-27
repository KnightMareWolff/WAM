/************************************************************************************/
/*Project: Whammy Bombs - WAM                                                       */
/*----------------------------------------------------------------------------------*/
/*                                 WAMGameMap                                       */
/*----------------------------------------------------------------------------------*/
/*Description:                                                                      */
/*The WAMGameMap Object are responsible for the Low Level Management of the Map used*/
/*This Object follow a Dinamic Programming Approach and will be used by some        */
/*navigations masks to make possible apply specific game rules during the gameplay. */
/*----------------------------------------------------------------------------------*/
/*Author: William D. Wolff - 2018                                                   */
/************************************************************************************/
#pragma once
#include "WAMGameMapNode.h"
#include "WAMGameMapData.h"

/**
 * 
 */
class WAM_API WAMGameMap
{
public:
	 WAMGameMap();
	 WAMGameMap(int pWAMSizeX, int pWAMSizeY);
	 WAMGameMap(UTexture2D   *pWAMTextureMap);
	 WAMGameMap(UDataTable   *pWAMMapDataTable, int pWAMMapSize);
	~WAMGameMap();

	static int              GetSizeX();
	static int              GetSizeY();
	static bool             Reset();
	static bool             Clear();
	static WAMGameMapNode*  GetNode     (int  x, int  y                                  );
	static WAMGameMapNode*  GetCenter   (                                                );
	static WAMGameMapNode*  GetNode     (FVector pWAM_Position                           );
	static WAMGameMapNode*  GetNode     (FVector pWAM_Position, int  &x  ,   int  &y     );
	static bool             SetNode     (int  x, int  y       , WAMGameMapNode* pWAM_Node);
	static bool             SetNode     (FVector pWAM_Position, WAMGameMapNode* pWAM_Node);
	static bool             SetSize     (int     pWAM_MapSize                            );
	static bool             BuildMap    (                                                );
	static bool             BuildMapTex (                                                );
	static bool             BuildMapData(                                                );


private:
	static WAMGameMapNode  ** pWAM_Map;
	static WAMGameMapNode  ** pWAM_MapL1;
	static WAMGameMapNode  ** pWAM_MapL2;
	static WAMGameMapNode  ** pWAM_MapL3;
	static WAMGameMapNode  ** pWAM_MapL4;
	static WAMGameMapNode  ** pWAM_MapL5;
	static WAMGameMapNode  ** pWAM_MapL6;
	static WAMGameMapNode  ** pWAM_MapL7;
	static WAMGameMapNode  ** pWAM_MapL8;
	static int                iWAM_SizeX;
	static int                iWAM_SizeY;
	static UTexture2D       * tWAM_TextureMap;
	static UDataTable       * tWAM_MapDataTable;
};
