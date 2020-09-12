//
// Created by rich on 3/7/20.
//

#ifndef HEAVENCLIENT_MEMBUF_H
#define HEAVENCLIENT_MEMBUF_H

#include <sstream>
#include <streambuf>

class membuf : public std::streambuf {
public:
    membuf(const char *data, unsigned int len);

private:
    int_type underflow() override;

    int_type uflow() override;

    int_type pbackfail(int_type ch) override;

    std::streamsize showmanyc() override;

    pos_type seekoff(off_type off,
                     std::ios_base::seekdir dir,
                     std::ios_base::openmode which) override;

    pos_type seekpos(pos_type sp_, std::ios_base::openmode which_) override;

    const char *const begin_;
    const char *const end_;
    const char *current_;
};

#endif  // HEAVENCLIENT_MEMBUF_H
