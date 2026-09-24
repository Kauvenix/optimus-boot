#include "initializer_list"
#include <array>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

#include <command.h>

void write_buffer(std::string &output, int pipefd) {
  std::array<char, 128> buffer;
  output.clear();

  ssize_t byte_read;
  while ((byte_read = read(pipefd, buffer.data(), buffer.size())) > 0) {
    output.append(buffer.data(), byte_read);
  }
}

namespace Command {
// This function was developed with AI assistance and may be improved
int start_process(const char *program, std::initializer_list<const char *> args,
                  std::string &output) {

  int pipefd[2];
  if (pipe(pipefd) == -1)
    return -1;

  pid_t pid = fork();

  if (pid < 0) {
    close(pipefd[0]);
    close(pipefd[1]);
    return -1;
  }

  if (pid == 0) {     // child
    close(pipefd[0]); // read

    if (dup2(pipefd[1], STDOUT_FILENO) == -1)
      _exit(1);

    close(pipefd[1]);

    // arguments manager
    std::vector<char *> argv;
    argv.push_back(const_cast<char *>(program));

    for (const char *arg : args)
      argv.push_back(const_cast<char *>(arg));

    argv.push_back(nullptr);
    // arguments manager end

    execvp(program, argv.data());
    std::cerr << "program = [" << program << "]\n";
    perror("execvp");
    _exit(127);
  }

  // Father
  close(pipefd[1]);

  write_buffer(output, pipefd[0]);

  close(pipefd[0]);

  int status;

  if (waitpid(pid, &status, 0) == -1)
    return -1;

  if (!WIFEXITED(status))
    return -1;

  // child exec error
  if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
    return -1;

  if (!output.empty() && output.back() == '\n')
    output.pop_back();
  return 0;
}
} // namespace Command
