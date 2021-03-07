#include <glad/glad.h>

using INDEX_TYPE = GLuint;
using PRECISION_TYPE = GLfloat;

// Window settings
#define WINDOW_WIDTH                                                        800
#define WINDOW_HEIGHT                                                       600

// Render settings
#define GRID_WIDTH                                                          101
#define GRID_HEIGHT                                                         101
#define STEPSIZE_X                                                          0.02f
#define STEPSIZE_Y                                                          0.02f
#define SPATIAL_DIMENSIONS                                                  3
#define COLOR_CHANNELS                                                      1
#define AMOUNT_OF_GRID_POINTS                                                    GRID_WIDTH * GRID_HEIGHT
#define AMOUNT_OF_TRIANGLES                                                 (GRID_WIDTH-1) * (GRID_HEIGHT-1)
#define AMOUNT_OF_TRIANGLE_INDICES                                          AMOUNT_OF_TRIANGLES * 3
#define AMOUNT_OF_TRIANGLE_INDICES_TOTAL                                    AMOUNT_OF_TRIANGLE_INDICES * 2

// Differential Equations settings
#define DIFF_EQ_DX                                                          1.0
#define DIFF_EQ_C                                                           5.0
#define DIFF_EQ_DT                                                          0.20 * (DIFF_EQ_DX * DIFF_EQ_DX) / (DIFF_EQ_C * DIFF_EQ_C)