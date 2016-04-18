ADD_LIBRARY(ioLib   Camera.h      Camera.cpp
		    BundlerBase.h BundlerBase.cpp 
		    PlyBase.h     PlyBase.cpp 
		    PatchBase.h   PatchBase.cpp
		    Face.h	  Face.cpp
	            Point.h       LBPNode.h
		    ANNWrapper.h  ANNWrapper.cpp
		     )
target_link_libraries(ioLib ${OpenCV_LIBS} libANN.a)

