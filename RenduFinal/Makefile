# Nom de l'exécutable
TARGET = main

# Compilateur
CXX = g++

# Options du compilateur
CXXFLAGS = -std=c++17 -Wall `pkg-config --cflags opencv4`

# Options de l'éditeur de liens
LDFLAGS = `pkg-config --libs opencv4`

# Fichiers source
SRCS = main.cpp

# Fichiers objets (générés à partir des sources)
OBJS = $(SRCS:.cpp=.o)

# Variables d'environnement
export LD_LIBRARY_PATH := /usr/local/lib:/lib/x86_64-linux-gnu:/usr/lib/x86_64-linux-gnu
export LD_PRELOAD := /lib/x86_64-linux-gnu/libpthread.so.0:/lib/x86_64-linux-gnu/libc.so.6

# Règle par défaut
all: $(TARGET)

# Règle pour construire l'exécutable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Règle pour compiler les fichiers sources en fichiers objets
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Règle pour exécuter le programme avec les variables d'environnement
run: $(TARGET)
	@echo "Setting environment variables..."
	@echo "LD_LIBRARY_PATH=$(LD_LIBRARY_PATH)"
	@echo "LD_PRELOAD=$(LD_PRELOAD)"
	./$(TARGET)

# Règle pour nettoyer les fichiers générés
clean:
	rm -f $(OBJS) $(TARGET)
# Nom de l'exécutable
TARGET = main

# Compilateur
CXX = g++

# Options du compilateur
CXXFLAGS = -std=c++17 -Wall `pkg-config --cflags opencv4`

# Options de l'éditeur de liens
LDFLAGS = `pkg-config --libs opencv4`

# Fichiers source
SRCS = main.cpp

# Fichiers objets (générés à partir des sources)
OBJS = $(SRCS:.cpp=.o)

# Variables d'environnement
export LD_LIBRARY_PATH := /usr/local/lib:/lib/x86_64-linux-gnu:/usr/lib/x86_64-linux-gnu
export LD_PRELOAD := /lib/x86_64-linux-gnu/libpthread.so.0:/lib/x86_64-linux-gnu/libc.so.6

# Règle par défaut
all: $(TARGET)

# Règle pour construire l'exécutable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Règle pour compiler les fichiers sources en fichiers objets
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Règle pour exécuter le programme avec les variables d'environnement
run: $(TARGET)
	@echo "Setting environment variables..."
	@echo "LD_LIBRARY_PATH=$(LD_LIBRARY_PATH)"
	@echo "LD_PRELOAD=$(LD_PRELOAD)"
	./$(TARGET)

# Règle pour nettoyer les fichiers générés
clean:
	rm -f $(OBJS) $(TARGET)
