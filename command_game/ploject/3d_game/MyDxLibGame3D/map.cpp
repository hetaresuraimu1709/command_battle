#include "Header.h"

Map::Map()
{
}

Map::~Map()
{
}

//bool Map::loadMapData(char * filename)
//{
//	FILE *fp;
//	fp = fopen(filename, "rt");
//
//	if (fp == NULL)
//	{
//		return false;
//	}
//
//	char buf[1024];
//	fgets(buf, 1024, fp);
//
//
//	char *token;
//
//	// マップデータ縦横読み込み
//	token = strtok(buf, ",");
//	mapXnum = atoi(token);
//
//	token = strtok(NULL, ",");
//	mapYnum = atoi(token);
//
//	token = strtok(NULL, ",");
//	graphchipSizeX = atoi(token);
//
//	token = strtok(NULL, ",");
//	graphchipSizeY = atoi(token);
//
//
//	//マップデータ配列確保
//	mapData = new unsigned char[mapXnum * mapYnum];
//
//	int x, y;
//	x = y = 0;
//	while (y < mapYnum)
//	{
//		//１行ごとに読み取り
//		fgets(buf, 1024, fp);
//		printf("%s", buf);
//
//		//第一トークン取得
//		token = strtok(buf, ",");
//
//		//１行をカンマ区切りで配列に取得
//		while (token != NULL || x < mapXnum)
//		{
//			mapData[x + y * mapXnum] = atoi(token);
//			token = strtok(NULL, ",");
//			x++;
//		}
//		x = 0;
//		y++;
//	}
//
//	fclose(fp);
//	return true;
//}
//
//bool Map::loadMapChip(char * chipGraphFilename)
//{
//	int tmp;
//	tmp = LoadGraph(chipGraphFilename);
//
//	if (tmp == -1)
//	{
//		return false;
//	}
//
//	int w, h;//画像の全体サイズ
//	GetGraphSize(tmp, &w, &h);
//
//	int xNum, yNum; //チップが縦横にいくつ並んでいるか？
//
//					//　マップチップ画像の画像内の縦横個数
//	xNum = w / graphchipSizeX;
//	yNum = h / graphchipSizeY;
//
//	// マップチップ画像配列確保
//	mapGraph = new int[xNum * yNum];
//
//	//マップチップ画像を分割して読み込み mapGraph配列が持つ
//	LoadDivGraph(chipGraphFilename, xNum * yNum, xNum, yNum, graphchipSizeX, graphchipSizeY, mapGraph);
//
//	return true;
//}
//
//void Map::mapDraw(int offsetX, int offsetY)
//{
//	int ix, iy;
//
//	// マップデータ→画像インデックスを取り出して画面に描画
//	for (iy = 0; iy < mapYnum; iy++)
//	{
//		for (ix = 0; ix < mapXnum; ix++)
//		{
//			DrawGraph(ix * graphchipSizeX - offsetX,
//				iy * graphchipSizeY - offsetY,
//				mapGraph[mapData[iy * mapXnum + ix]], FALSE);
//		}
//	}
//}
//
//void Map::mapRelease()
//{
//	if (mapGraph)
//	{
//		delete[] mapGraph;
//	}
//	if (mapData)
//	{
//		delete[] mapData;
//	}
//	mapGraph = NULL;
//	mapData = NULL;
//}

void Map::Init()
{
	graph[0]  = MV1LoadModel("data/field/grass.x");
	graph[1]  = MV1LoadModel("data/field/wall.x");
	graph[2]  = MV1LoadModel("data/field/warp.x");
	sky_model = MV1LoadModel("data/model/Skydome_N8/Dome_N802.x");
	sky_graph = LoadGraph("data/field/sky.png");
	for (int i = 0; i < 3; i++)
	{
		cloud_graph[i] = LoadGraph("data/field/cloud.png");
		cloud_pos[i] = VectorGet(0.0f + (i * 2000.0f), 0.0f);
	}
	map_ground[0] = MV1DuplicateModel(graph[0]);
	map_ground[1] = MV1DuplicateModel(graph[1]);
	map_ground[2] = MV1DuplicateModel(graph[2]);
	now_floor = 1;
}

void Map::Draw(int map_data[BATTLE_MAP_CHIP][BATTLE_MAP_CHIP])
{
	for (int i = 0; i < BATTLE_MAP_CHIP; i++)
	{
		for (int j = 0; j < BATTLE_MAP_CHIP; j++)
		{
			for (int f = 0; f < 3; f++)
			{
				if (map_data[i][j] == f)
				{
					MV1SetPosition(map_ground[f], VGet(50.f*j, 0.f, 50.f*i));
					MV1DrawModel(map_ground[f]);
				}
			}
		}
	}
}

void Map::Cloud_P_Move()
{
	for (int i = 0; i < 3; i++)
	{
		cloud_pos[i].x += 5.5f;
	}
}

void Map::Cloud_M_Move()
{
	for (int i = 0; i < 3; i++)
	{
		cloud_pos[i].x -= 4.5f;
	}
}

void Map::Sky_Draw()
{
	DrawGraph(0, 0, sky_graph, true);
	for (int i = 0; i < 3; i++)
	{
		cloud_pos[i].x -= 0.5f;
		if (cloud_pos[i].x < -2000.0f)
		{
			cloud_pos[i].x = 4000.0f;
		}
		if (cloud_pos[i].x > 4000.0f)
		{
			cloud_pos[i].x = -2000.0f;
		}
		DrawGraph((int)cloud_pos[i].x, (int)cloud_pos[i].y, cloud_graph[0], true);
	}
}

void Map::Field_Draw(Effect *effect)
{
	Sky_Draw();
	switch (now_floor)
	{
	case 1:
		Draw(map_data_1);
		break;
	case 2:
		Draw(map_data_2);
		break;
	case 3:
		Draw(map_data_3);
		break;
	default:
		Draw(battle_map_data);
		break;
	}
}

void Map::Battle_Draw()
{
	Sky_Draw();
	Draw(battle_map_data);
}

//*******************************
//ブロックの当たり判定の前準備
//*******************************
//x座標よりマップの添え字番号を得る
int Map::GetMapIndexX(float x)
{
	return (int)(x / MAP_BLOCK_SIZE);
}
//z座標よりマップの添え字番号を得る
int Map::GetMapIndexZ(float z)
{
	return (int)(z / MAP_BLOCK_SIZE);
}
//x座標、y座標よりマップの種類を返す
int Map::GetMapType(float x, float z, int map_data[BATTLE_MAP_CHIP][BATTLE_MAP_CHIP] ,Map *map)
{
	//描写範囲内なら描写する
	if ((x > 0 && x < MAP_BLOCK_SIZE*BATTLE_MAP_CHIP) &&
		(z > 0 && z < MAP_BLOCK_SIZE*BATTLE_MAP_CHIP))
	{
		return map_data[GetMapIndexZ(z)][GetMapIndexX(x)];
	}
	return -1;
}