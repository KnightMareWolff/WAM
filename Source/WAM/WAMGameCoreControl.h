/************************************************************************************/
/*Project: Whammy Bombs - WAM                                                       */
/*----------------------------------------------------------------------------------*/
/*                                 WAMGameCoreControl                               */
/*----------------------------------------------------------------------------------*/
/*Description:                                                                      */
/*The WAMGameCoreControl Object are responsible for the execution of low level fucts*/
/*since the Unreal Library Interface have the advantage of make the low level avali */
/*able to the High Level Prt, buuut , all of them are static and not work as normal */
/*C++ Classes and Functions.                                                        */
/*So, The Game Core Control will act as a Manager of all internal functions coded in*/
/*the core of the game... ;)                                                        */
/*----------------------------------------------------------------------------------*/
/*Author: William D. Wolff - 2018                                                   */
/************************************************************************************/
#pragma once
#include "WAMGameMap.h"
#include "WAMGamePlayer.h"
#include "WAMGameExplosion.h"
#include "WAMGamePathfinder.h"

/**
 * 
 */
class WAM_API WAMGameCoreControl
{
public:
	 WAMGameCoreControl();
	 WAMGameCoreControl(int pWAMSizeX               , int pWAMSizeY );
	 WAMGameCoreControl(UTexture2D *pWAMTextureMap                  );
	 WAMGameCoreControl(UDataTable *pWAMMapDataTable,int pWAMMapSize);
	~WAMGameCoreControl();

	//Get Functions
	TArray<WAMGameMapNode*> GetMapNodes     (                                     );
	TArray<WAMGameMapNode*> GetMapFlags     (                                     );
	TArray<WAMGameMapNode*> GetImpactedNodes(                                     );
	WAMGamePlayer        *  GetPlayer       (int pWAM_PlayerId                    );
	FVector                 GetCenterMap    (                                     );
	bool                    GetGameStatus   (                                     );
	WAMGameMapNode       *  GetRandomFlag   (                                     );
	//Set Functions
	bool                    SetMapSize      (int pWAM_MapSize                     );
	
	//Create Functions
	bool                    CreateMap       (int pWAMSizeX, int pWAMSizeY         );
	bool                    CreateMap       (UDataTable *pWAMMapDataTable,int pWAMMapSize);
	bool                    CreateMap       (UTexture2D *pWAMTextureMap           );
	bool                    CreateObjects   (int pWAMSizeX, int pWAMSizeY         );
	bool                    CreateObjects   (UTexture2D *pWAMTextureMap           );
	bool                    CreateObjects   (UDataTable *pWAMMapDataTable,int pWAMMapSize);
	bool                    CreatePlayers   (                                     );
	bool                    CreateElements  (                                     );

	//Game Core Functions
	bool                    UpdateBlock(WAMGameMapNode* pWAM_UpdatedBlock);
	bool                    MovePlayer(int pWAM_PlayerId, int pWAM_Direction);
	bool                    ThrowBomb(int pWAM_PlayerId);
	bool                    ThrowExplosion(FVector pWAM_BombLocation);
	TArray<WAMGameMapNode*> FindPath      (FVector pWAM_Begin       , FVector pWAM_End);
	

private:
	WAMGameMap            *  pWAM_GameMap;
	WAMGamePathfinder     *  pWAM_PathFinder;
	TArray<WAMGameMapNode *> pWAM_GameMapNodesArray;
	TArray<WAMGameMapNode *> pWAM_GameImpactedArray;
	TArray<WAMGameMapNode *> pWAM_GameFlagArray;
	WAMGamePlayer         *  Player01;
	WAMGamePlayer         *  Player02;
	WAMGameExplosion      *  Explosion;
	bool                     pWAM_GameOk;
};
