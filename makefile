EXE = BrickBreaker

CFLAGS   = -g `sdl2-config --cflags`
CXXFLAGS = -Wall -g `sdl2-config --cflags` -std=c++11
LDFLAGS  = `sdl2-config --libs` \
           -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_gfx -lm

INCLUDE = -I"/usr/include/SDL"

# All C++ source files of the project
CXXFILES   = $(shell find src -maxdepth 1 -type f -name '*.cpp')
CXXOBJECTS = $(CXXFILES:.cpp=.o)

SOURCES = $(CXXFILES)
OBJECTS = $(CXXOBJECTS)

ifdef V
MUTE =
VTAG = -v
else
MUTE = @
endif

all: $(EXE)
	# Build successful!

$(EXE): $(OBJECTS)
	# Linking...
	$(MUTE)$(CXX) $(OBJECTS) -o $(EXE) $(LDFLAGS)

src/%.o: src/%.cpp
	# Compiling $<...
	$(MUTE)$(CXX) $(CXXFLAGS) $(INCLUDE) $< -c -o $@
	$(BUILD)

src/%.o: src/%.c
	# Compiling $<...
	$(MUTE)$(CC) $(CFLAGS) $(INCLUDE) $< -c -o $@

run: all
	$(MUTE)./$(EXE)

clean:
	# Cleaning...
	-$(MUTE)rm -f $(EXE) $(OBJECTS)