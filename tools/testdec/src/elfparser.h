#ifndef MIPSDEC_ELFPARSER_H
#define MIPSDEC_ELFPARSER_H

#include <string>
#include <memory>
#include <cstdint>

#include <gelf.h>

class ELFParser final {
  ELFParser() = delete;
  ELFParser &operator=(const ELFParser &other) = delete;
  ELFParser(const ELFParser& other) = delete;

  struct PrivateData;
  std::unique_ptr<PrivateData> d;

public:
  ELFParser(const std::string &image_path);
  ~ELFParser();

  bool is64bit() const noexcept;
  bool littleEndian() const noexcept;
  std::uint16_t architecture() const noexcept;
  std::uintmax_t entryPoint() const noexcept;

  void read(std::uint8_t *buffer, std::size_t size) const;
  void read(std::uintmax_t virtual_address, std::uint8_t *buffer, std::size_t size) const;

  void seek(std::uintmax_t virtual_address) const noexcept;
  std::uintmax_t tell() const noexcept;

  std::uint8_t u8() const;
  std::uint16_t u16() const;
  std::uint32_t u32() const;
  std::uint64_t u64() const;

  std::int8_t i8() const;
  std::int16_t i16() const;
  std::int32_t i32() const;
  std::int64_t i64() const;

private:
  void parseHeader();
  void parseProgramHeaderTable();
  void parseSectionList();
  bool offsetFromVirtualAddress(std::uintmax_t &offset, std::size_t &available_bytes, std::uintmax_t virtual_address) const noexcept;
};

#endif  // MIPSDEC_ELFPARSER_H