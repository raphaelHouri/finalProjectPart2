cmake_minimum_required(VERSION 3.14.3)
project(finalProjectPart2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(finalProjectPart2 main.cpp ClientHandler.h FileCacheManager.cpp FileCacheManager.h MyClientHandler.cpp MyClientHandler.h Server.h MyParallelServer.cpp MyParallelServer.h MySerialServer.cpp MySerialServer.h StringReverser.cpp  StringReverser.h Solver.h CacheManager.h Searcher.h Searchable.h State.h Matrix.h Matrix.cpp Main.h DataStrucForSearcher.h SearcherSolver.h MyPriorityQueue.h SearcherAbstract.h BFSSearcher.h AStarSearcher.h BestFirstSearcher.h DFSSearcher.h DFSSearcher.h)