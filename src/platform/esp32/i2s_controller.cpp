#include "platform/esp32/i2s_controller.h"


ess_error_t i2s_controller::setup(int flags = 0) {
  if(m_bCreated) return ESS_OK;

  m_i2sConfig.sample_rate = ess_format_get_samplerate(ESS_DEFAULT_SERVER_FORMAT);
  m_i2sConfig.bits_per_sample = (i2s_bits_per_sample_t)ess_format_get_bits(ESS_DEFAULT_SERVER_FORMAT);

  m_i2sConfig.mode = (i2s_mode_t) (I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_RX);                                /
  m_i2sConfig.channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT;                           //2-channels
  m_i2sConfig.communication_format =(i2s_comm_format_t)(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB);
  m_i2sConfig.dma_buf_count = ESS_BACKEND_I2S_DMA_BUF_COUNT;
  m_i2sConfig.dma_buf_len = ESS_BACKEND_I2S_DMA_BUF_SIZE;                                                      //
  m_i2sConfig.intr_alloc_flags = ESP_INTR_FLAG_LEVEL1;                                //Interrupt level 1
  m_i2sConfig.use_apll = 1;

  m_pinConfig.bck_io_num = I2S_EXTERNAL_DAC_BCK;
  m_pinConfig.ws_io_num = I2S_EXTERNAL_DAC_LRCLK;
  m_pinConfig.data_out_num = I2S_EXTERNAL_DAC_DOUT;
  m_pinConfig.data_in_num = I2S_EXTERNAL_DAC_DIN;                                                       //Not used

  if(i2s_driver_install((i2s_port_t)0, &m_i2sConfig, 0, NULL) != ESP_OK) {
    return ESS_ERROR;
  }
  if(i2s_set_pin((i2s_port_t)0, &m_pinConfig) != ESP_OK) {
    return ESS_ERROR;
  }



  i2s_set_clk((i2s_port_t)0, m_i2sConfig.sample_rate,
                         m_i2sConfig.bits_per_sample,
                        ( (ess_format_get_channels(ESS_DEFAULT_SERVER_FORMAT) == 2) ?
                          I2S_CHANNEL_STEREO :
                          I2S_CHANNEL_MONO) );
                          
  m_bCreated = true;

  return ESS_OK;
}
ess_error_t i2s_controller::destroy(int flags)  {
    return ESS_OK;
}
ess_format_t i2s_controller::get_format() { return ESS_DEFAULT_SERVER_FORMAT; }
int i2s_controller::get_bits() { return m_i2sConfig.bits_per_sample ; }
int i2s_controller::get_samplerate() { return m_i2sConfig.sample_rate; }
int i2s_controller::get_channels() { return ess_format_get_channels(ESS_DEFAULT_SERVER_FORMAT) ; }
