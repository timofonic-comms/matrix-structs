FILES=`find include tests -type f -type f \( -iname "*.cpp" -o -iname "*.hpp" \)`

build-debug:
	@cmake -DBUILD_TESTS=OFF -H. -GNinja -Bbuild -DCMAKE_BUILD_TYPE=Debug
	@cmake --build build

build-release-debug:
	@cmake -DBUILD_TESTS=OFF -H. -GNinja -Bbuild -DCMAKE_BUILD_TYPE=RelWithDebInfo
	@cmake --build build

build-release:
	@cmake -DBUILD_TESTS=OFF -H. -GNinja -Bbuild -DCMAKE_BUILD_TYPE=Release
	@cmake --build build

test:
	@cmake -DBUILD_TESTS=ON -H. -GNinja -Bbuild -DCMAKE_BUILD_TYPE=Debug
	@cmake --build build
	@cd build && GTEST_COLOR=1 ctest --verbose

lint:
	@clang-format -i ${FILES} && git diff --exit-code

clean:
	rm -rf build

.PHONY: build
