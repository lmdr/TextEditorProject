editor : EditorTest.o ECTextViewImp.o EditorApplication.o \
				EditorBuilder.o EditorCommand.o EditorCommandHistory.o \
				EditorComposableParagraph.o EditorComposer.o EditorController.o \
				EditorDocument.o EditorKeyHandler.o EditorLine.o EditorLineBreakStrategy.o \
				EditorModel.o EditorPage.o EditorParagraph.o EditorParser.o EditorView.o
				g++ -o editor EditorTest.o ECTextViewImp.o EditorApplication.o \
								EditorBuilder.o EditorCommand.o EditorCommandHistory.o \
								EditorComposableParagraph.o EditorComposer.o EditorController.o \
								EditorDocument.o EditorKeyHandler.o EditorLine.o EditorLineBreakStrategy.o \
								EditorModel.o EditorPage.o EditorParagraph.o EditorParser.o EditorView.o

EditorTest.o : EditorTest.cpp
				g++ -Wall -g -std=c++11 -c -o EditorTest.o -c EditorTest.cpp

ECTextViewImp.o : ECTextViewImp.cpp
				g++ -Wall -g -std=c++11 -c -o ECTextViewImp.o -c ECTextViewImp.cpp

EditorApplication.o : EditorApplication.cpp
				g++ -Wall -g -std=c++11 -c -o EditorApplication.o -c EditorApplication.cpp

EditorBuilder.o : EditorBuilder.cpp
				g++ -Wall -g -std=c++11 -c -o EditorBuilder.o -c EditorBuilder.cpp

EditorCommand.o : EditorCommand.cpp
				g++ -Wall -g -std=c++11 -c -o EditorCommand.o -c EditorCommand.cpp

EditorCommandHistory.o : EditorCommandHistory.cpp
				g++ -Wall -g -std=c++11 -c -o EditorCommandHistory.o -c EditorCommandHistory.cpp

EditorComposableParagraph.o : EditorComposableParagraph.cpp
				g++ -Wall -g -std=c++11 -c -o EditorComposableParagraph.o -c EditorComposableParagraph.cpp

EditorComposer.o : EditorComposer.cpp
				g++ -Wall -g -std=c++11 -c -o EditorComposer.o -c EditorComposer.cpp

EditorController.o : EditorController.cpp
				g++ -Wall -g -std=c++11 -c -o EditorController.o -c EditorController.cpp

EditorDocument.o : EditorDocument.cpp
				g++ -Wall -g -std=c++11 -c -o EditorDocument.o -c EditorDocument.cpp

EditorKeyHandler.o : EditorKeyHandler.cpp
				g++ -Wall -g -std=c++11 -c -o EditorKeyHandler.o -c EditorKeyHandler.cpp

EditorLine.o : EditorLine.cpp
				g++ -Wall -g -std=c++11 -c -o EditorLine.o -c EditorLine.cpp

EditorLineBreakStrategy.o : EditorLineBreakStrategy.cpp
				g++ -Wall -g -std=c++11 -c -o EditorLineBreakStrategy.o -c EditorLineBreakStrategy.cpp

EditorModel.o : EditorModel.cpp
				g++ -Wall -g -std=c++11 -c -o EditorModel.o -c EditorModel.cpp

EditorPage.o : EditorPage.cpp
				g++ -Wall -g -std=c++11 -c -o EditorPage.o -c EditorPage.cpp

EditorParagraph.o : EditorParagraph.cpp
				g++ -Wall -g -std=c++11 -c -o EditorParagraph.o -c EditorParagraph.cpp

EditorParser.o : EditorParser.cpp
				g++ -Wall -g -std=c++11 -c -o EditorParser.o EditorParser.cpp

EditorView.o : EditorView.cpp
				g++ -Wall -g -std=c++11 -c -o EditorView.o -c EditorView.cpp

clean :
				rm *.o

ultraclean : clean
				rm editor