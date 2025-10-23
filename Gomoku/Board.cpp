#include "Board.h"
#include <mmsyscom.h>

int Board::grid_pixel_pos(int index){
	return kMargin + index * kGridSize;
}

Board::Board(const int board_dimension, const int board_size, const int margin, const int piece_size):
    kBoardDimension(board_dimension),kBoardSize(board_size),kMargin(margin),kGridSize((kBoardSize-2*kMargin)*1.0/(kBoardDimension-1)),kPieceSize(piece_size){
	printf("Board created: dimension=%d, size=%d, margin=%d, grid size=%.2f\n", kBoardDimension, kBoardSize, kMargin, kGridSize);
	board_state.resize(kBoardDimension, std::vector<PieceType>(kBoardDimension, kNoPiece));
}

void Board::Init() {
	loadimage(&board_img, "asset/board.png", kBoardSize, kBoardSize);
	loadimage(&black_piece_img, "asset/black_piece.png");
	loadimage(&white_piece_img, "asset/white_piece.png");

	putimage(0, 0, &board_img);
}

static double distance(double x1, double y1, double x2, double y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

bool Board::Click(int x, int y, PiecePos *pos) {
	static const double offset = kGridSize * 0.3;
	int col = (x - kMargin) / kGridSize;
	int row = (y - kMargin) / kGridSize;

	auto CheckDis = [&](int _col, int _row) {
		double pixel_x = kMargin + _col * kGridSize;
		double pixel_y = kMargin + _row * kGridSize;
		if (distance(x, y, pixel_x, pixel_y) <= offset) {
			pos->col = _col;
			pos->row = _row;
			return true;
		}
		return false;
	};

	// Check the four nearest grid points
	if (CheckDis(col, row))return true;
	if (CheckDis(col + 1, row))return true;
	if (CheckDis(col, row + 1))return true;
	if (CheckDis(col + 1, row + 1))return true;
	
	return false;
}

//Enable PNG images
//https://blog.csdn.net/weixin_45779485/article/details/102757315
static void putimagePNG(int x, int y, IMAGE* picture){
	DWORD* dst = GetImageBuffer();
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture);
	int picture_width = picture->getwidth();
	int picture_height = picture->getheight();
	int graphWidth = getwidth();
	int graphHeight = getheight();
	int dstX = 0;

	//Cp=¦Áp*FP+(1-¦Áp)*BP
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width;
			int sa = ((src[srcX] & 0xff000000) >> 24);
			int sr = ((src[srcX] & 0xff0000) >> 16);
			int sg = ((src[srcX] & 0xff00) >> 8);
			int sb = src[srcX] & 0xff;
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth;
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //Cp=¦Áp*FP+(1-¦Áp)*BP; ¦Áp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //¦Áp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //¦Áp=sa/255 , FP=sb , BP=db
			}
		}
	}
}

void Board::PlacePiece(const PiecePos *pos, PieceType type) {
	board_state[pos->row][pos->col] = type;
	int x = grid_pixel_pos(pos->col) - kPieceSize / 2;
	int y = grid_pixel_pos(pos->row) - kPieceSize / 2;
	if (type == kWhitePiece) {
		putimagePNG(x, y, &white_piece_img);
	}
	else {
		putimagePNG(x, y, &black_piece_img);
	}
}

PieceType Board::get_piece_type(const PiecePos *pos) {
	return board_state[pos->row][pos->col];
}

std::vector<std::vector<PieceType>> Board::get_board_state() {
	return board_state;
}