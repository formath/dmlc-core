#include <cstdlib>
#include <cstdio>
#include <dmlc/io.h>
#include <dmlc/timer.h>
#include "../src/data/libfm_parser.h"

int main(int argc, char *argv[]) {
  if (argc < 5) {
    printf("Usage: <libfm> partid npart nthread\n");
    return 0;
  }
  using namespace dmlc;
  InputSplit *split = InputSplit::Create(argv[1],
                                         atoi(argv[2]),
                                         atoi(argv[3]),
                                         "text");
  int nthread = atoi(argv[4]);
  data::LibFMParser<uint64_t> parser(split, nthread);
  while (parser.Next()) {
    const dmlc::RowBlock<uint64_t>& batch_data = parser.Value();
    for (size_t i = 0; i < batch_data.size; i++) {
      std::cout << batch_data[i].to_string() << std::endl;
    }
  }
  return 0;
}