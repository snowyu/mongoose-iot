#ifndef _STUB_FLASHER_H_
#define _STUB_FLASHER_H_

enum stub_cmd {
  /*
   * Erase a region of SPI flash.
   *
   * Args: addr, len; must be FLASH_SECTOR_SIZE-aligned.
   * Input: None.
   * Output: None.
   */
  CMD_FLASH_ERASE = 0,

  /*
   * Write to the SPI flash.
   *
   * Args: addr, len, erase; addr and len must be SECTOR_SIZE-aligned.
   *       If erase != 0, perform erase before writing.
   * Input: Stream of data to be written, note: no SLIP encapsulation here.
   * Output: SLIP packets with number of bytes written after every write.
   *         This can (and should) be used for flow control. Flasher will
   *         write in 1K chunks but will buffer up to 4K of data
   *         Use this feedback to keep buffer above 1K but below 4K.
   *         Final packet will contain MD5 digest of the data written.
   */
  CMD_FLASH_WRITE = 1,

  /*
   * Read from the SPI flash.
   *
   * Args: addr, len, block_size; no alignment requirements, block_size <= 4K.
   * Input: None.
   * Output: Packets of up to block_size with data.
   *         Last packet is the MD5 digest of the data.
   *
   * Note: No flow control is performed, it is assumed that the host can cope
   * with the inbound stream.
   */
  CMD_FLASH_READ = 2,

  /*
   * Compute MD5 digest of the specified flash region.
   *
   * Args: addr, len, digest_block_size; no alignment requirements.
   * Input: None.
   * Output: If block digests are not enabled (digest_block_size == 0),
   *         only overall digest is produced.
   *         Otherwise, there will be a separate digest for each block,
   *         the remainder (if any) and the overall digest at the end.
   */
  CMD_FLASH_DIGEST = 3,

  /*
   * Read flash chip ID.
   * This is the JEDEC ID, containinf manufactirer, SPI mode and capacity.
   *
   * Args: None.
   * Input: None.
   * Output: 32 bit chip id (only 24 bits are meaningful).
   */
  CMD_FLASH_READ_CHIP_ID = 4,

  /*
   * Zap the whole chip at once.
   *
   * Args: None.
   * Input: None.
   * Output: None.
   */
  CMD_FLASH_ERASE_CHIP = 5,

  /*
   * Boots the firmware from flash.
   *
   * Args: None.
   * Input: None.
   * Output: None.
   */
  CMD_BOOT_FW = 6,

  /*
   * Reboot the CPU.
   * Since strapping settings are not reset, this will reboot into whatever mode
   * got us here, most likely UART loader.
   *
   * Args: None.
   * Input: None.
   * Output: None.
   */
  CMD_REBOOT = 7,
};

#endif /* _STUB_FLASHER_H_ */
