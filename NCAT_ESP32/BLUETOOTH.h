#if BLUETOOTH

#define MYUNIHID                     ///Custom HID parser ENABLE 
#define UNI_PLATFORM_PC_DEBUG        /// This must be set! For UNIHID
#define L2CAP_USES_CHANNELS          /// Better for more Bluetooth Devices
#define BTSTACK_PSMALLOC                 ///BT PSMALLOC ENABLE...


#define CONFIG_BLUEPAD32_GAP_SECURITY //THIS IS NEEDED FOR BLUETOOTH KEYBOARDS SUPPORT...


/// #define BTJOY_DURATION_MULTIPLIER 1


#define INQUIRY_INTERVAL 5



#include "BLEUUID.h"                    // for manual connection... (esp_bt_controller_init)!
#include "esp_bt.h"                     // for esp_bt_controller_mem_release


#define HAVE_BTSTACK_STDIN

#ifndef I2S_COMM_FORMAT_STAND_I2S
#define I2S_COMM_FORMAT_STAND_I2S I2S_COMM_FORMAT_I2S
#endif

#define HAVE_FREERTOS_TASK_NOTIFICATIONS  
#define ESP_PLATFORM
#define HAVE_EMBEDDED_TIME_MS
#define HAVE_FREERTOS_INCLUDE_PREFIX


// Internal ring buffer: ~21 kB
#define HCI_HOST_ACL_PACKET_LEN 1024 ///
#define HCI_HOST_ACL_PACKET_NUM 20 ///
#define HCI_HOST_SCO_PACKET_LEN 60 ///
#define HCI_HOST_SCO_PACKET_NUM 10 ///

#define ENABLE_PRINTF_HEXDUMP

#include "btstack/src/btstack.h"

uint8_t a2dp_and_avrcp_inited=0;

//--------------------------------------------------------------------------------
#include "btstack_esp32/btstack_port_esp32.h"

#include "btstack_esp32/btstack_port_esp32.c"
#include "btstack_esp32/btstack_run_loop_freertos.c" 
#include "btstack_esp32/btstack_tlv_esp32.c" 
#include "btstack_esp32/btstack_audio_esp32.c"
#include "btstack_esp32/btstack_stdin_esp32.c"

//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
#include "btstack/src/btstack_config.h"
#include "btstack/src/btstack.h"
#include "btstack/src/l2cap.h"
#include "btstack/src/hci.c"
#include "btstack/src/hci_dump.c"
#include "btstack/src/hci_cmd.c"
#include "btstack/src/l2cap.c"
#include "btstack/src/btstack_hid_parser.c" 
#include "btstack/src/l2cap_signaling.c"
#include "btstack/src/ad_parser.c"
#include "btstack/src/btstack_ring_buffer.c"
#include "btstack/src/btstack_run_loop.c"
#include "btstack/src/btstack_util.c"
#include "btstack/src/btstack_memory.c"
#include "btstack/src/btstack_tlv.c"
#include "btstack/src/btstack_linked_list.c"
#include "btstack/src/btstack_audio.c"
#include "btstack/src/btstack_resample.c"
#include "btstack/src/btstack_crypto.c"
#include "btstack/src/btstack_memory_pool.c"
//--------------------------------------------------------------------------------
#include "btstack/src/classic/sdp_client.c" 
#include "btstack/src/classic/sdp_util.c"
#include "btstack/src/classic/btstack_link_key_db_tlv.c"
#include "btstack/src/classic/avrcp.c"
#include "btstack/src/classic/avrcp_controller.c"
#include "btstack/src/classic/device_id_server.c"
#include "btstack/src/classic/sdp_server.c"
#include "btstack/src/classic/a2dp_sink.c"
#include "btstack/src/classic/avdtp.c"
#include "btstack/src/classic/avdtp_sink.c"
#include "btstack/src/classic/avdtp_source.c"
#include "btstack/src/classic/avdtp_util.c"
#include "btstack/src/classic/avrcp_target.c"
#include "btstack/src/classic/btstack_sbc_decoder_bluedroid.c"
#include "btstack/src/classic/btstack_sbc_encoder_bluedroid.c"
#include "btstack/src/classic/avdtp_acceptor.c"
#include "btstack/src/classic/avdtp_initiator.c"
#include "btstack/src/classic/btstack_sbc_plc.c"
#include "btstack/src/classic/a2dp_source.c"
#include "btstack/src/classic/spp_server.c"
#include "btstack/src/classic/rfcomm.c" 

#include "btstack/src/classic/hid_host.c"

#include "btstack/src/ble/le_device_db_tlv.c"
#include "btstack/src/ble/sm.c"
#include "btstack/src/ble/gatt_client.c"
#include "btstack/src/ble/att_dispatch.c"

#include "btstack/src/ble/gatt-service/hids_client.c"

#include "btstack/3rd-party/rijndael/rijndael.c"
//--------------------------------------------------------------------------------
#include "btstack/3rd-party/bluedroid/decoder/srce/decoder-sbc.c"
#include "btstack/3rd-party/bluedroid/decoder/srce/framing.c"
#include "btstack/3rd-party/bluedroid/decoder/srce/decoder-private.c"
#include "btstack/3rd-party/bluedroid/decoder/srce/dequant.c"
#include "btstack/3rd-party/bluedroid/decoder/srce/bitstream-decode.c"
#include "btstack/3rd-party/bluedroid/decoder/srce/alloc.c"
#include "btstack/3rd-party/bluedroid/decoder/srce/bitalloc-sbc.c"
#include "btstack/3rd-party/bluedroid/decoder/srce/synthesis-sbc.c"
#include "btstack/3rd-party/bluedroid/decoder/srce/bitalloc.c"
#include "btstack/3rd-party/bluedroid/decoder/srce/synthesis-dct8.c"
#include "btstack/3rd-party/bluedroid/decoder/srce/synthesis-8-generated.c"

#include "btstack/platform/posix/wav_util.c" ///
//--------------------------------------------------------------------------------

///#define CONFIG_BLUEPAD32_PLATFORM_ARDUINO        /// 
#define CONFIG_BLUEPAD32_PLATFORM_PC_DEBUG ///
//--------------------------------------------------------------------------------
#include "bluepad32/uni_bluetooth.c"
#include "bluepad32/uni_hid_device.c"
#include "bluepad32/uni_hid_parser_8bitdo.c"
#include "bluepad32/uni_hid_parser_android.c"
#include "bluepad32/uni_hid_parser_ds3.c"
#include "bluepad32/uni_hid_parser_ds4.c"
#include "bluepad32/uni_hid_parser_ds5.c"
#include "bluepad32/uni_hid_parser_generic.c"
#include "bluepad32/uni_hid_parser_icade.c"
#include "bluepad32/uni_hid_parser_nimbus.c"
#include "bluepad32/uni_hid_parser_ouya.c"
#include "bluepad32/uni_hid_parser_smarttvremote.c"
#include "bluepad32/uni_hid_parser_switch.c"
#include "bluepad32/uni_hid_parser_wii.c"
#include "bluepad32/uni_hid_parser_xboxone.c"
#include "bluepad32/uni_hid_parser.c" ///
#include "bluepad32/uni_utils.c" 
#include "bluepad32/uni_gamepad.c"
#include "bluepad32/uni_circular_buffer.c"
#include "bluepad32/uni_joystick.c"


#include "bluepad32/uni_platform.c"
#include "bluepad32/uni_platform_pc_debug.c"
///#include "bluepad32/uni_platform_unijoysticle.c"
#include "bluepad32/uni_platform_arduino.c"
#include "bluepad32/uni_platform_arduino_bootstrap.cpp"
#include "bluepad32/uni_bt_conn.c"

//--------------------------------------------------------------------------------

uint8_t STREAM_PAUSED;

//█████████████████████████████████████████████████
uint8_t START_BT() {
  printf("BLUETOOTH BTSTACK HCI_POWER_ON...");
  hci_power_control(HCI_POWER_ON);
  printf("[ OK ]\n"); 
  return 1; 
}
//█████████████████████████████████████████████████
uint8_t SLEEP_BT() {
  printf("BLUETOOTH BTSTACK HCI_POWER_SLEEP...");
  hci_power_control(HCI_POWER_SLEEP);
  printf("[ OK ]\n");  
  return 1; 
}
//█████████████████████████████████████████████████
#ifdef MYUNIHID

//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
static void start_scan(void) {
if (BLUETOOTH_APP==2) { //HID packet handler
#if DEBUG>4
  logi("--> Scanning for new devices...\n");
#endif   
  ///vTaskDelay(1000); //do not use this !

  //do not stop scan... rapidly decrease performance (and if is connected PS4 joystick then freeze after ~1min.)
#if BLUETOOTH_STOP_SCAN_AFTER_CONNECTED
  if (BLUETOOTH_CONNECTIONS>0) gap_inquiry_stop();
  else 
#endif  
  gap_inquiry_start(INQUIRY_INTERVAL);

}  
}
//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒

/*
static void packet_handler_(uint8_t packet_type, uint16_t channel, uint8_t* packet, uint16_t size);

//--------------------------------------------------------------------------------
static void l2cap_create_control_connection(uni_hid_device_t* d) {
  uint8_t status =
      l2cap_create_channel(packet_handler_, d->address, PSM_HID_CONTROL, L2CAP_CHANNEL_MTU, &d->hid_control_cid);
  if (status) {
    loge("\nConnecting or Auth to HID Control failed: 0x%02x", status);
  } else {
    uni_hid_device_set_state(d, STATE_L2CAP_CONTROL_CONNECTION_REQUESTED);
  }
}
//--------------------------------------------------------------------------------
static void l2cap_create_interrupt_connection(uni_hid_device_t* d) {
  uint8_t status =
      l2cap_create_channel(packet_handler_, d->address, PSM_HID_INTERRUPT,
                           L2CAP_CHANNEL_MTU, &d->hid_interrupt_cid);
  if (status) {
    loge("\nConnecting or Auth to HID Interrupt failed: 0x%02x", status);
  } else {
    uni_hid_device_set_state(d, STATE_L2CAP_INTERRUPT_CONNECTION_REQUESTED);
  }
}
//--------------------------------------------------------------------------------
*/
#endif







//********************************************************************************
// A2DP SINK BLUETOOTH
//********************************************************************************
//#define AVRCP_BROWSING_ENABLED

// if volume control not supported by btstack_audio_sink, you can try to disable volume change notification
// to force the A2DP Source to reduce volume by attenuating the audio stream
#define SUPPORT_VOLUME_CHANGE_NOTIFICATION

#ifdef HAVE_BTSTACK_STDIN
#include "btstack/src/btstack_stdin.h"
#endif

#include "btstack/src/btstack_ring_buffer.h"

#ifdef HAVE_POSIX_FILE_IO  //not ! (cause crash in A2DP sink ... not implemented file write...)
#include "btstack/platform/posix/wav_util.h"

#define STORE_TO_SBC_FILE 
#define STORE_TO_WAV_FILE 
#endif

#define NUM_CHANNELS 2
#define BYTES_PER_FRAME     (2*NUM_CHANNELS)
#define MAX_SBC_FRAME_SIZE 120

// SBC Decoder for WAV file or live playback
static btstack_sbc_decoder_state_t state;
static btstack_sbc_mode_t mode = SBC_MODE_STANDARD;

// ring buffer for SBC Frames
// below 30: add samples, 30-40: fine, above 40: drop samples
#define OPTIMAL_FRAMES_MIN 30
#define OPTIMAL_FRAMES_MAX 40
#define ADDITIONAL_FRAMES  20
///static uint8_t sbc_frame_storage[(OPTIMAL_FRAMES_MAX + ADDITIONAL_FRAMES) * MAX_SBC_FRAME_SIZE];
static uint8_t* sbc_frame_storage; ///

static btstack_ring_buffer_t sbc_frame_ring_buffer;
static unsigned int sbc_frame_size;

// rest buffer for not fully used sbc frames, with additional frames for resampling
///static uint8_t decoded_audio_storage[(128+16) * BYTES_PER_FRAME];
static uint8_t* decoded_audio_storage; ///
static btstack_ring_buffer_t decoded_audio_ring_buffer;
 
static int audio_stream_started;

// temp storage of lower-layer request
static int16_t * request_buffer;
static int       request_frames;

#define STORE_FROM_PLAYBACK

// WAV File
#ifdef STORE_TO_WAV_FILE
static uint32_t audio_frame_count = 0;
static char * wav_filename = "a2dp_sink_demo.wav";
#endif

#ifdef STORE_TO_SBC_FILE    
static FILE * sbc_file;
static char * sbc_filename = "av2dp_sink_demo.sbc";
#endif

typedef struct media_codec_configuration_sbc_s { ///
    int reconfigure;

    int num_channels;
    int sampling_frequency;
    int block_length;
    int subbands;
    int min_bitpool_value;
    int max_bitpool_value;
    btstack_sbc_channel_mode_t      channel_mode;
    btstack_sbc_allocation_method_t allocation_method;
} media_codec_configuration_sbc_t;

static media_codec_configuration_sbc_t sbc_configuration;
static int volume_percentage = 0; 
static avrcp_battery_status_t battery_status = AVRCP_BATTERY_STATUS_WARNING; 

#ifdef HAVE_BTSTACK_STDIN
// pts:         
static const char * device_addr_string = "5C:F3:70:60:7B:87";
// mac 2013:  static const char * device_addr_string = "84:38:35:65:d1:15";
// iPhone 5S: static const char * device_addr_string = "54:E4:3A:26:A2:39";
static bd_addr_t device_addr;
#endif

static btstack_packet_callback_registration_t A2DP_hci_event_callback_registration; ///

///static uint8_t  sdp_avdtp_sink_service_buffer[150];
///static uint8_t  sdp_avrcp_target_service_buffer[150];
///static uint8_t  sdp_avrcp_controller_service_buffer[200];
///static uint8_t  device_id_sdp_service_buffer[100];
static uint8_t*  sdp_avdtp_sink_service_buffer; ///
static uint8_t*  sdp_avrcp_target_service_buffer; ///
static uint8_t*  sdp_avrcp_controller_service_buffer; ///
static uint8_t*  device_id_sdp_service_buffer; ///

static uint16_t a2dp_cid = 0;
static uint8_t  a2dp_local_seid = 0;

static uint16_t avrcp_cid = 0;
static uint8_t  avrcp_connected = 0;
///static uint8_t  avrcp_subevent_value[255];
static uint8_t*  avrcp_subevent_value;

static uint8_t media_sbc_codec_capabilities[] = {
    0xFF,//(AVDTP_SBC_44100 << 4) | AVDTP_SBC_STEREO,
    0xFF,//(AVDTP_SBC_BLOCK_LENGTH_16 << 4) | (AVDTP_SBC_SUBBANDS_8 << 2) | AVDTP_SBC_ALLOCATION_METHOD_LOUDNESS,
    2, 53
}; 

static uint8_t media_sbc_codec_configuration[4]; 

static int media_initialized = 0;
static btstack_resample_t resample_instance;

/* @section Main Application Setup
 *
 * @text The Listing MainConfiguration shows how to setup AD2P Sink and AVRCP services. 
 * Besides calling init() method for each service, you'll also need to register several packet handlers:
 * - hci_packet_handler - handles legacy pairing, here by using fixed '0000' pin code.
 * - a2dp_sink_packet_handler - handles events on stream connection status (established, released), the media codec configuration, and, the status of the stream itself (opened, paused, stopped).
 * - handle_l2cap_media_data_packet - used to receive streaming data. If STORE_TO_WAV_FILE directive (check btstack_config.h) is used, the SBC decoder will be used to decode the SBC data into PCM frames. The resulting PCM frames are then processed in the SBC Decoder callback.
 * - avrcp_packet_handler - receives connect/disconnect event.
 * - avrcp_controller_packet_handler - receives answers for sent AVRCP commands.
 * - avrcp_target_packet_handler - receives AVRCP commands, and registered notifications.
 * - stdin_process - used to trigger AVRCP commands to the A2DP Source device, such are get now playing info, start, stop, volume control. Requires HAVE_BTSTACK_STDIN.
 *
 * @text To announce A2DP Sink and AVRCP services, you need to create corresponding
 * SDP records and register them with the SDP service. 
 *
 * @text Note, currently only the SBC codec is supported. 
 * If you want to store the audio data in a file, you'll need to define STORE_TO_WAV_FILE. 
 * If STORE_TO_WAV_FILE directive is defined, the SBC decoder needs to get initialized when a2dp_sink_packet_handler receives event A2DP_SUBEVENT_STREAM_STARTED. 
 * The initialization of the SBC decoder requires a callback that handles PCM data:
 * - handle_pcm_data - handles PCM audio frames. Here, they are stored a in wav file if STORE_TO_WAV_FILE is defined, and/or played using the audio library.
 */

/* LISTING_START(MainConfiguration): Setup Audio Sink and AVRCP services */
static void hci_packet_handler(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size);
static void a2dp_sink_packet_handler(uint8_t packet_type, uint16_t channel, uint8_t * event, uint16_t event_size);
static void handle_l2cap_media_data_packet(uint8_t seid, uint8_t *packet, uint16_t size);
static void A2DP_avrcp_packet_handler(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size); ///
static void A2DP_avrcp_controller_packet_handler(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size); ///
static void A2DP_avrcp_target_packet_handler(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size); ///
#ifdef HAVE_BTSTACK_STDIN
static void stdin_process(char cmd);
#endif

static int a2dp_and_avrcp_setup(void){
//--------------------------------------------------------------------------------
    gap_set_allow_role_switch(true); ///YES THIS
    gap_set_local_name("NCAT_SPEAKER 00:00:00:00:00:00"); 
    gap_set_class_of_device(0x200408); //headset ID
    gap_discoverable_control(1); ///
    gap_secure_connections_enable(false); ///disable secured connections
    gap_set_security_level((gap_security_level_t)0); /// A2DP SINK not using secured connections
//--------------------------------------------------------------------------------

    l2cap_init(); ///already inited...?

#ifdef ENABLE_BLE
    // Initialize LE Security Manager. Needed for cross-transport key derivation
    sm_init();
#endif

    // Initialize AVDTP Sink
    a2dp_sink_init();
    a2dp_sink_register_packet_handler(&a2dp_sink_packet_handler);
    a2dp_sink_register_media_handler(&handle_l2cap_media_data_packet);

    // Create stream endpoint
    avdtp_stream_endpoint_t * local_stream_endpoint = a2dp_sink_create_stream_endpoint(AVDTP_AUDIO, 
        AVDTP_CODEC_SBC, media_sbc_codec_capabilities, sizeof(media_sbc_codec_capabilities), 
        media_sbc_codec_configuration, sizeof(media_sbc_codec_configuration));
    if (!local_stream_endpoint){
        printf("A2DP Sink: not enough memory to create local stream endpoint\n");
        return 1;
    }

    // Store stream enpoint's SEP ID, as it is used by A2DP API to indentify the stream endpoint
    a2dp_local_seid = avdtp_local_seid(local_stream_endpoint);

    // Initialize AVRCP service
    avrcp_init();
    avrcp_register_packet_handler(&A2DP_avrcp_packet_handler); ///

    // Initialize AVRCP Controller
    avrcp_controller_init();
    avrcp_controller_register_packet_handler(&A2DP_avrcp_controller_packet_handler);
    
     // Initialize AVRCP Target
    avrcp_target_init();
    avrcp_target_register_packet_handler(&A2DP_avrcp_target_packet_handler);
    
    // Initialize SDP 
    sdp_init();

    // Create A2DP Sink service record and register it with SDP
    ///memset(sdp_avdtp_sink_service_buffer, 0, sizeof(sdp_avdtp_sink_service_buffer));
    memset(sdp_avdtp_sink_service_buffer, 0, 150); ///
    
    a2dp_sink_create_sdp_record(sdp_avdtp_sink_service_buffer, 0x10001, AVDTP_SINK_FEATURE_MASK_HEADPHONE, NULL, NULL);
    sdp_register_service(sdp_avdtp_sink_service_buffer);

    // Create AVRCP Controller service record and register it with SDP. We send Category 1 commands to the media player, e.g. play/pause
    ///memset(sdp_avrcp_controller_service_buffer, 0, sizeof(sdp_avrcp_controller_service_buffer));
    memset(sdp_avrcp_controller_service_buffer, 0, 200); ///
    
    uint16_t controller_supported_features = AVRCP_FEATURE_MASK_CATEGORY_PLAYER_OR_RECORDER;
#ifdef AVRCP_BROWSING_ENABLED
    controller_supported_features |= AVRCP_FEATURE_MASK_BROWSING;
#endif
    avrcp_controller_create_sdp_record(sdp_avrcp_controller_service_buffer, 0x10002, controller_supported_features, NULL, NULL);
    sdp_register_service(sdp_avrcp_controller_service_buffer);
    
    // Create AVRCP Target service record and register it with SDP. We receive Category 2 commands from the media player, e.g. volume up/down
    ///memset(sdp_avrcp_target_service_buffer, 0, sizeof(sdp_avrcp_target_service_buffer));
    memset(sdp_avrcp_target_service_buffer, 0, 150); ///
    
    uint16_t target_supported_features = AVRCP_FEATURE_MASK_CATEGORY_MONITOR_OR_AMPLIFIER;
    avrcp_target_create_sdp_record(sdp_avrcp_target_service_buffer, 0x10003, target_supported_features, NULL, NULL);
    sdp_register_service(sdp_avrcp_target_service_buffer);

    // Create Device ID (PnP) service record and register it with SDP
    ///memset(device_id_sdp_service_buffer, 0, sizeof(device_id_sdp_service_buffer));
    memset(device_id_sdp_service_buffer, 0, 100); ///
    
    device_id_create_sdp_record(device_id_sdp_service_buffer, 0x10004, DEVICE_ID_VENDOR_ID_SOURCE_BLUETOOTH, BLUETOOTH_COMPANY_ID_BLUEKITCHEN_GMBH, 1, 1);
    sdp_register_service(device_id_sdp_service_buffer);

    // Set local name with a template Bluetooth address, that will be automatically
    // replaced with a actual address once it is available, i.e. when BTstack boots
    // up and starts talking to a Bluetooth module.
    ///gap_set_local_name("A2DP Sink Demo 00:00:00:00:00:00");
    gap_discoverable_control(1);
    gap_set_class_of_device(0x200408);

    // Register for HCI events
    A2DP_hci_event_callback_registration.callback = &hci_packet_handler; ///
    hci_add_event_handler(&A2DP_hci_event_callback_registration); ///

#ifdef HAVE_POSIX_FILE_IO
    if (!btstack_audio_sink_get_instance()){
        printf("No audio playback.\n");
    } else {
        printf("Audio playback supported.\n");
    }
#ifdef STORE_TO_WAV_FILE 
   printf("Audio will be stored to \'%s\' file.\n",  wav_filename);
#endif
#endif
    return 0;
}
/* LISTING_END */

static void playback_handler(int16_t * buffer, uint16_t num_audio_frames){

#ifdef STORE_TO_WAV_FILE
    int       wav_samples = num_audio_frames * NUM_CHANNELS;
    int16_t * wav_buffer  = buffer;
#endif
    
    // called from lower-layer but guaranteed to be on main thread
    if (sbc_frame_size == 0){
        memset(buffer, 0, num_audio_frames * BYTES_PER_FRAME);
        return;
    }

    // first fill from resampled audio
    uint32_t bytes_read;
    btstack_ring_buffer_read(&decoded_audio_ring_buffer, (uint8_t *) buffer, num_audio_frames * BYTES_PER_FRAME, &bytes_read);
    buffer          += bytes_read / NUM_CHANNELS;
    num_audio_frames   -= bytes_read / BYTES_PER_FRAME;

    // then start decoding sbc frames using request_* globals
    request_buffer = buffer;
    request_frames = num_audio_frames;
    while (request_frames && btstack_ring_buffer_bytes_available(&sbc_frame_ring_buffer) >= sbc_frame_size){
        // decode frame
        uint8_t sbc_frame[MAX_SBC_FRAME_SIZE];
        btstack_ring_buffer_read(&sbc_frame_ring_buffer, sbc_frame, sbc_frame_size, &bytes_read);
        btstack_sbc_decoder_process_data(&state, 0, sbc_frame, sbc_frame_size);
    }

#ifdef STORE_TO_WAV_FILE
    audio_frame_count += num_audio_frames;
    wav_writer_write_int16(wav_samples, wav_buffer);
#endif
}

static void handle_pcm_data(int16_t * data, int num_audio_frames, int num_channels, int sample_rate, void * context){
    UNUSED(sample_rate);
    UNUSED(context);
    UNUSED(num_channels);   // must be stereo == 2

    const btstack_audio_sink_t * audio_sink = btstack_audio_sink_get_instance();
    if (!audio_sink){
#ifdef STORE_TO_WAV_FILE
        audio_frame_count += num_audio_frames;
        wav_writer_write_int16(num_audio_frames * NUM_CHANNELS, data);
#endif
        return;
    }

    // resample into request buffer - add some additional space for resampling
    int16_t  output_buffer[(128+16) * NUM_CHANNELS]; // 16 * 8 * 2
    uint32_t resampled_frames = btstack_resample_block(&resample_instance, data, num_audio_frames, output_buffer);

    // store data in btstack_audio buffer first
    int frames_to_copy = btstack_min(resampled_frames, request_frames);
    memcpy(request_buffer, output_buffer, frames_to_copy * BYTES_PER_FRAME);
    request_frames  -= frames_to_copy;
    request_buffer  += frames_to_copy * NUM_CHANNELS;

    // and rest in ring buffer
    int frames_to_store = resampled_frames - frames_to_copy;
    if (frames_to_store){
        int status = btstack_ring_buffer_write(&decoded_audio_ring_buffer, (uint8_t *)&output_buffer[frames_to_copy * NUM_CHANNELS], frames_to_store * BYTES_PER_FRAME);
        if (status){
            printf("Error storing samples in PCM ring buffer!!!\n");
        }
    }
}

static int media_processing_init(media_codec_configuration_sbc_t configuration); ///
static int media_processing_init(media_codec_configuration_sbc_t configuration){
    if (media_initialized) return 0;

    btstack_sbc_decoder_init(&state, mode, handle_pcm_data, NULL);

#ifdef STORE_TO_WAV_FILE
    wav_writer_open(wav_filename, configuration.num_channels, configuration.sampling_frequency);
#endif

#ifdef STORE_TO_SBC_FILE    
   sbc_file = fopen(sbc_filename, "wb"); 
#endif

///    btstack_ring_buffer_init(&sbc_frame_ring_buffer, sbc_frame_storage, sizeof(sbc_frame_storage));
    btstack_ring_buffer_init(&sbc_frame_ring_buffer, sbc_frame_storage, (OPTIMAL_FRAMES_MAX + ADDITIONAL_FRAMES) * MAX_SBC_FRAME_SIZE); ///
    
///    btstack_ring_buffer_init(&decoded_audio_ring_buffer, decoded_audio_storage, sizeof(decoded_audio_storage));
    btstack_ring_buffer_init(&decoded_audio_ring_buffer, decoded_audio_storage, (128+16) * BYTES_PER_FRAME); ///

    
    btstack_resample_init(&resample_instance, configuration.num_channels);

    // setup audio playback
    const btstack_audio_sink_t * audio = btstack_audio_sink_get_instance();
    if (audio){
        audio->init(NUM_CHANNELS, configuration.sampling_frequency, &playback_handler);
    }

    audio_stream_started = 0;
    media_initialized = 1;
    return 0;
}

static void media_processing_start(void){
    if (!media_initialized) return;
    // setup audio playback
    const btstack_audio_sink_t * audio = btstack_audio_sink_get_instance();
    if (audio){
        audio->start_stream();
    }
    audio_stream_started = 1;
}

static void media_processing_pause(void){
    if (!media_initialized) return;
    // stop audio playback
    audio_stream_started = 0;
    const btstack_audio_sink_t * audio = btstack_audio_sink_get_instance();
    if (audio){
        audio->stop_stream();
    }
}

static void media_processing_close(void){
    if (!media_initialized) return;
    media_initialized = 0;
    audio_stream_started = 0;
    sbc_frame_size = 0;

#ifdef STORE_TO_WAV_FILE                 
    wav_writer_close();
    uint32_t total_frames_nr = state.good_frames_nr + state.bad_frames_nr + state.zero_frames_nr;

    printf("WAV Writer: Decoding done. Processed %u SBC frames:\n - %d good\n - %d bad\n", total_frames_nr, state.good_frames_nr, total_frames_nr - state.good_frames_nr);
    printf("WAV Writer: Wrote %u audio frames to wav file: %s\n", audio_frame_count, wav_filename);
#endif

#ifdef STORE_TO_SBC_FILE
    fclose(sbc_file);
#endif     

    // stop audio playback
    const btstack_audio_sink_t * audio = btstack_audio_sink_get_instance();
    if (audio){
        printf("close stream\n");
        audio->close();
    }
}

/* @section Handle Media Data Packet 
 *
 * @text Here the audio data, are received through the handle_l2cap_media_data_packet callback.
 * Currently, only the SBC media codec is supported. Hence, the media data consists of the media packet header and the SBC packet.
 * The SBC frame will be stored in a ring buffer for later processing (instead of decoding it to PCM right away which would require a much larger buffer).
 * If the audio stream wasn't started already and there are enough SBC frames in the ring buffer, start playback.
 */ 

static int read_media_data_header(uint8_t * packet, int size, int * offset, avdtp_media_packet_header_t * media_header);
static int read_sbc_header(uint8_t * packet, int size, int * offset, avdtp_sbc_codec_header_t * sbc_header);

static void handle_l2cap_media_data_packet(uint8_t seid, uint8_t *packet, uint16_t size){
    UNUSED(seid);
    int pos = 0;
     
    avdtp_media_packet_header_t media_header;
    if (!read_media_data_header(packet, size, &pos, &media_header)) return;
    
    avdtp_sbc_codec_header_t sbc_header;
    if (!read_sbc_header(packet, size, &pos, &sbc_header)) return;

#ifdef STORE_TO_SBC_FILE
    fwrite(packet+pos, size-pos, 1, sbc_file);
#endif

    const btstack_audio_sink_t * audio = btstack_audio_sink_get_instance();
    // process data right away if there's no audio implementation active, e.g. on posix systems to store as .wav
    if (!audio){
        btstack_sbc_decoder_process_data(&state, 0, packet+pos, size-pos);
        return;
    }

    // store sbc frame size for buffer management
    sbc_frame_size = (size-pos)/ sbc_header.num_frames;
        
    int status = btstack_ring_buffer_write(&sbc_frame_ring_buffer, packet+pos, size-pos);
    if (status != ERROR_CODE_SUCCESS){
        printf("Error storing samples in SBC ring buffer!!!\n");
    }

    // decide on audio sync drift based on number of sbc frames in queue
    int sbc_frames_in_buffer = btstack_ring_buffer_bytes_available(&sbc_frame_ring_buffer) / sbc_frame_size;
    uint32_t resampling_factor;

    // nomimal factor (fixed-point 2^16) and compensation offset
    uint32_t nomimal_factor = 0x10000;
    uint32_t compensation   = 0x00100;

    if (sbc_frames_in_buffer < OPTIMAL_FRAMES_MIN){
      resampling_factor = nomimal_factor - compensation;    // stretch samples
    } else if (sbc_frames_in_buffer <= OPTIMAL_FRAMES_MAX){
      resampling_factor = nomimal_factor;                   // nothing to do
    } else {
      resampling_factor = nomimal_factor + compensation;    // compress samples
    }

    btstack_resample_set_factor(&resample_instance, resampling_factor);

    // start stream if enough frames buffered
    if (!audio_stream_started && sbc_frames_in_buffer >= OPTIMAL_FRAMES_MIN){
        media_processing_start();
    }
}

static int read_sbc_header(uint8_t * packet, int size, int * offset, avdtp_sbc_codec_header_t * sbc_header){
    int sbc_header_len = 12; // without crc
    int pos = *offset;
    
    if (size - pos < sbc_header_len){
        printf("Not enough data to read SBC header, expected %d, received %d\n", sbc_header_len, size-pos);
        return 0;
    }

    sbc_header->fragmentation = get_bit16(packet[pos], 7);
    sbc_header->starting_packet = get_bit16(packet[pos], 6);
    sbc_header->last_packet = get_bit16(packet[pos], 5);
    sbc_header->num_frames = packet[pos] & 0x0f;
    pos++;
    *offset = pos;
    return 1;
}

static int read_media_data_header(uint8_t *packet, int size, int *offset, avdtp_media_packet_header_t *media_header); ///
static int read_media_data_header(uint8_t *packet, int size, int *offset, avdtp_media_packet_header_t *media_header){
    int media_header_len = 12; // without crc
    int pos = *offset;
    
    if (size - pos < media_header_len){
        printf("Not enough data to read media packet header, expected %d, received %d\n", media_header_len, size-pos);
        return 0;
    }

    media_header->version = packet[pos] & 0x03;
    media_header->padding = get_bit16(packet[pos],2);
    media_header->extension = get_bit16(packet[pos],3);
    media_header->csrc_count = (packet[pos] >> 4) & 0x0F;
    pos++;

    media_header->marker = get_bit16(packet[pos],0);
    media_header->payload_type  = (packet[pos] >> 1) & 0x7F;
    pos++;

    media_header->sequence_number = big_endian_read_16(packet, pos);
    pos+=2;

    media_header->timestamp = big_endian_read_32(packet, pos);
    pos+=4;

    media_header->synchronization_source = big_endian_read_32(packet, pos);
    pos+=4;
    *offset = pos;
    return 1;
}

static void dump_sbc_configuration(media_codec_configuration_sbc_t configuration);
static void dump_sbc_configuration(media_codec_configuration_sbc_t configuration){
    printf("    - num_channels: %d\n", configuration.num_channels);
    printf("    - sampling_frequency: %d\n", configuration.sampling_frequency);
    printf("    - channel_mode: %d\n", configuration.channel_mode);
    printf("    - block_length: %d\n", configuration.block_length);
    printf("    - subbands: %d\n", configuration.subbands);
    printf("    - allocation_method: %d\n", configuration.allocation_method);
    printf("    - bitpool_value [%d, %d] \n", configuration.min_bitpool_value, configuration.max_bitpool_value);
    printf("\n");
}

static void A2DP_avrcp_packet_handler(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size){ ///
    UNUSED(channel);
    UNUSED(size);
    uint16_t local_cid;
    uint8_t  status;
    bd_addr_t address;
    
    if (packet_type != HCI_EVENT_PACKET) return;
    if (hci_event_packet_get_type(packet) != HCI_EVENT_AVRCP_META) return;
    switch (packet[2]){
        case AVRCP_SUBEVENT_CONNECTION_ESTABLISHED: {
            local_cid = avrcp_subevent_connection_established_get_avrcp_cid(packet);
            status = avrcp_subevent_connection_established_get_status(packet);
            if (status != ERROR_CODE_SUCCESS){
                printf("AVRCP: Connection failed: status 0x%02x\n", status);
                avrcp_cid = 0;
                return;
            }
            
            avrcp_cid = local_cid;
            avrcp_connected = 1;
            avrcp_subevent_connection_established_get_bd_addr(packet, address);
            printf("AVRCP: Connected to %s, cid 0x%02x\n", bd_addr_to_str(address), avrcp_cid);

            avrcp_target_support_event(avrcp_cid, AVRCP_NOTIFICATION_EVENT_VOLUME_CHANGED);
            avrcp_target_support_event(avrcp_cid, AVRCP_NOTIFICATION_EVENT_BATT_STATUS_CHANGED);
            avrcp_target_battery_status_changed(avrcp_cid, battery_status);
    
            // automatically enable notifications
            avrcp_controller_enable_notification(avrcp_cid, AVRCP_NOTIFICATION_EVENT_PLAYBACK_STATUS_CHANGED);
            avrcp_controller_enable_notification(avrcp_cid, AVRCP_NOTIFICATION_EVENT_NOW_PLAYING_CONTENT_CHANGED);
            avrcp_controller_enable_notification(avrcp_cid, AVRCP_NOTIFICATION_EVENT_TRACK_CHANGED);
            return;
        }
        
        case AVRCP_SUBEVENT_CONNECTION_RELEASED:
            printf("AVRCP: Channel released: cid 0x%02x\n", avrcp_subevent_connection_released_get_avrcp_cid(packet));
            avrcp_cid = 0;
            avrcp_connected = 0;
            return;
        default:
            break;
    }
}

static void A2DP_avrcp_controller_packet_handler(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size){
    UNUSED(channel);
    UNUSED(size);
    
    if (packet_type != HCI_EVENT_PACKET) return;
    if (hci_event_packet_get_type(packet) != HCI_EVENT_AVRCP_META) return;
    if (!avrcp_cid) return;

    ///memset(avrcp_subevent_value, 0, sizeof(avrcp_subevent_value));
    memset(avrcp_subevent_value, 0, 255); ///
    switch (packet[2]){
        case AVRCP_SUBEVENT_NOTIFICATION_PLAYBACK_POS_CHANGED:
            printf("AVRCP Controller: Playback position changed, position %d ms\n", (unsigned int) avrcp_subevent_notification_playback_pos_changed_get_playback_position_ms(packet));
            break;
        case AVRCP_SUBEVENT_NOTIFICATION_PLAYBACK_STATUS_CHANGED:
            printf("AVRCP Controller: Playback status changed %s\n", avrcp_play_status2str(avrcp_subevent_notification_playback_status_changed_get_play_status(packet)));
            return;
        case AVRCP_SUBEVENT_NOTIFICATION_NOW_PLAYING_CONTENT_CHANGED:
            printf("AVRCP Controller: Playing content changed\n");
            return;
        case AVRCP_SUBEVENT_NOTIFICATION_TRACK_CHANGED:
            printf("AVRCP Controller: Track changed\n");
            return;
        case AVRCP_SUBEVENT_NOTIFICATION_AVAILABLE_PLAYERS_CHANGED:
            printf("AVRCP Controller: Changed\n");
            return; 
        case AVRCP_SUBEVENT_SHUFFLE_AND_REPEAT_MODE:{
            uint8_t shuffle_mode = avrcp_subevent_shuffle_and_repeat_mode_get_shuffle_mode(packet);
            uint8_t repeat_mode  = avrcp_subevent_shuffle_and_repeat_mode_get_repeat_mode(packet);
            printf("AVRCP Controller: %s, %s\n", avrcp_shuffle2str(shuffle_mode), avrcp_repeat2str(repeat_mode));
            break;
        }
        case AVRCP_SUBEVENT_NOW_PLAYING_TRACK_INFO:
            printf("AVRCP Controller:     Track: %d\n", avrcp_subevent_now_playing_track_info_get_track(packet));
            break;

        case AVRCP_SUBEVENT_NOW_PLAYING_TOTAL_TRACKS_INFO:
            printf("AVRCP Controller:     Total Tracks: %d\n", avrcp_subevent_now_playing_total_tracks_info_get_total_tracks(packet));
            break;

        case AVRCP_SUBEVENT_NOW_PLAYING_TITLE_INFO:
            if (avrcp_subevent_now_playing_title_info_get_value_len(packet) > 0){
                memcpy(avrcp_subevent_value, avrcp_subevent_now_playing_title_info_get_value(packet), avrcp_subevent_now_playing_title_info_get_value_len(packet));
                printf("AVRCP Controller:     Title: %s\n", avrcp_subevent_value);
            }  
            break;

        case AVRCP_SUBEVENT_NOW_PLAYING_ARTIST_INFO:
            if (avrcp_subevent_now_playing_artist_info_get_value_len(packet) > 0){
                memcpy(avrcp_subevent_value, avrcp_subevent_now_playing_artist_info_get_value(packet), avrcp_subevent_now_playing_artist_info_get_value_len(packet));
                printf("AVRCP Controller:     Artist: %s\n", avrcp_subevent_value);
            }  
            break;
        
        case AVRCP_SUBEVENT_NOW_PLAYING_ALBUM_INFO:
            if (avrcp_subevent_now_playing_album_info_get_value_len(packet) > 0){
                memcpy(avrcp_subevent_value, avrcp_subevent_now_playing_album_info_get_value(packet), avrcp_subevent_now_playing_album_info_get_value_len(packet));
                printf("AVRCP Controller:     Album: %s\n", avrcp_subevent_value);
            }  
            break;
        
        case AVRCP_SUBEVENT_NOW_PLAYING_GENRE_INFO:
            if (avrcp_subevent_now_playing_genre_info_get_value_len(packet) > 0){
                memcpy(avrcp_subevent_value, avrcp_subevent_now_playing_genre_info_get_value(packet), avrcp_subevent_now_playing_genre_info_get_value_len(packet));
                printf("AVRCP Controller:     Genre: %s\n", avrcp_subevent_value);
            }  
            break;
        
        case AVRCP_SUBEVENT_PLAY_STATUS:
            printf("AVRCP Controller: Song length %"PRIu32" ms, Song position %"PRIu32" ms, Play status %s\n", 
                avrcp_subevent_play_status_get_song_length(packet), 
                avrcp_subevent_play_status_get_song_position(packet),
                avrcp_play_status2str(avrcp_subevent_play_status_get_play_status(packet)));
            break;
        
        case AVRCP_SUBEVENT_OPERATION_COMPLETE:
            printf("AVRCP Controller: %s complete\n", avrcp_operation2str(avrcp_subevent_operation_complete_get_operation_id(packet)));
            break;
        
        case AVRCP_SUBEVENT_OPERATION_START:
            printf("AVRCP Controller: %s start\n", avrcp_operation2str(avrcp_subevent_operation_start_get_operation_id(packet)));
            break;
       
        case AVRCP_SUBEVENT_NOTIFICATION_EVENT_TRACK_REACHED_END:
            printf("AVRCP Controller: Track reached end\n");
            break;

        case AVRCP_SUBEVENT_PLAYER_APPLICATION_VALUE_RESPONSE:
            printf("AVRCP Controller: Set Player App Value %s\n", avrcp_ctype2str(avrcp_subevent_player_application_value_response_get_command_type(packet)));
            break;
            
        default:
            break;
    }  
}

static void avrcp_volume_changed(uint8_t volume){
    const btstack_audio_sink_t * audio = btstack_audio_sink_get_instance();
    if (audio){
        audio->set_volume(volume);
//--------------------------------------------------------------------------------
VOLUME=volume*2;
//--------------------------------------------------------------------------------                
    }
}

static void A2DP_avrcp_target_packet_handler(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size){ ///
    UNUSED(channel);
    UNUSED(size);

    if (packet_type != HCI_EVENT_PACKET) return;
    if (hci_event_packet_get_type(packet) != HCI_EVENT_AVRCP_META) return;
    
    uint8_t volume;
    char const * button_state;
    avrcp_operation_id_t operation_id;

    switch (packet[2]){
        case AVRCP_SUBEVENT_NOTIFICATION_VOLUME_CHANGED:
            volume = avrcp_subevent_notification_volume_changed_get_absolute_volume(packet);
            volume_percentage = volume * 100 / 127;
            printf("AVRCP Target    : Volume set to %d%% (%d)\n", volume_percentage, volume);
            avrcp_volume_changed(volume);
            break;
        
        case AVRCP_SUBEVENT_OPERATION:
            operation_id = (avrcp_operation_id_t)avrcp_subevent_operation_get_operation_id(packet);
            button_state = avrcp_subevent_operation_get_button_pressed(packet) > 0 ? "PRESS" : "RELEASE";
            switch (operation_id){
                case AVRCP_OPERATION_ID_VOLUME_UP:
                    printf("AVRCP Target    : VOLUME UP (%s)\n", button_state);
                    break;
                case AVRCP_OPERATION_ID_VOLUME_DOWN:
                    printf("AVRCP Target    : VOLUME UP (%s)\n", button_state);
                    break;
                default:
                    return;
            }
            break;
        default:
            printf("AVRCP Target    : Event 0x%02x is not parsed\n", packet[2]);
            break;
    }
}

static void hci_packet_handler(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size){
    UNUSED(channel);
    UNUSED(size);
    if (packet_type != HCI_EVENT_PACKET) return;
    if (hci_event_packet_get_type(packet) == HCI_EVENT_PIN_CODE_REQUEST) {
        bd_addr_t address;
        printf("Pin code request - using '0000'\n");
        hci_event_pin_code_request_get_bd_addr(packet, address);
        gap_pin_code_response(address, "0000");
    }
}

static void a2dp_sink_packet_handler(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size){
    UNUSED(channel);
    UNUSED(size);
    bd_addr_t address;
    uint8_t status;

    uint8_t allocation_method;

    if (packet_type != HCI_EVENT_PACKET) return;
    if (hci_event_packet_get_type(packet) != HCI_EVENT_A2DP_META) return;

    switch (packet[2]){
        case A2DP_SUBEVENT_SIGNALING_MEDIA_CODEC_OTHER_CONFIGURATION:
            printf("A2DP  Sink      : Received non SBC codec - not implemented\n");
            break;
        case A2DP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CONFIGURATION:{
            printf("A2DP  Sink      : Received SBC codec configuration\n");
            sbc_configuration.reconfigure = a2dp_subevent_signaling_media_codec_sbc_configuration_get_reconfigure(packet);
            sbc_configuration.num_channels = a2dp_subevent_signaling_media_codec_sbc_configuration_get_num_channels(packet);
            sbc_configuration.sampling_frequency = a2dp_subevent_signaling_media_codec_sbc_configuration_get_sampling_frequency(packet);
            sbc_configuration.block_length = a2dp_subevent_signaling_media_codec_sbc_configuration_get_block_length(packet);
            sbc_configuration.subbands = a2dp_subevent_signaling_media_codec_sbc_configuration_get_subbands(packet);
            sbc_configuration.min_bitpool_value = a2dp_subevent_signaling_media_codec_sbc_configuration_get_min_bitpool_value(packet);
            sbc_configuration.max_bitpool_value = a2dp_subevent_signaling_media_codec_sbc_configuration_get_max_bitpool_value(packet);
            
            allocation_method = a2dp_subevent_signaling_media_codec_sbc_configuration_get_allocation_method(packet);
            
            // Adapt Bluetooth spec definition to SBC Encoder expected input
            sbc_configuration.allocation_method = (btstack_sbc_allocation_method_t)(allocation_method - 1);
           
            switch (a2dp_subevent_signaling_media_codec_sbc_configuration_get_channel_mode(packet)){
                case AVDTP_CHANNEL_MODE_JOINT_STEREO:
                    sbc_configuration.channel_mode = SBC_CHANNEL_MODE_JOINT_STEREO;
                    break;
                case AVDTP_CHANNEL_MODE_STEREO:
                    sbc_configuration.channel_mode = SBC_CHANNEL_MODE_STEREO;
                    break;
                case AVDTP_CHANNEL_MODE_DUAL_CHANNEL:
                    sbc_configuration.channel_mode = SBC_CHANNEL_MODE_DUAL_CHANNEL;
                    break;
                case AVDTP_CHANNEL_MODE_MONO:
                    sbc_configuration.channel_mode = SBC_CHANNEL_MODE_MONO;
                    break;
                default:
                    btstack_assert(false);
                    break;
            }
            dump_sbc_configuration(sbc_configuration);

            if (sbc_configuration.reconfigure){
                media_processing_close();
            }
            // prepare media processing
            media_processing_init(sbc_configuration);
            break;
        }  
        case A2DP_SUBEVENT_STREAM_ESTABLISHED:
            a2dp_subevent_stream_established_get_bd_addr(packet, address);
            status = a2dp_subevent_stream_established_get_status(packet);
            if (status != ERROR_CODE_SUCCESS){
                printf("A2DP  Sink      : Streaming connection failed, status 0x%02x\n", status);
                break;
            }
            
            a2dp_cid = a2dp_subevent_stream_established_get_a2dp_cid(packet);
            printf("A2DP  Sink      : Streaming connection is established, address %s, cid 0x%02X, local seid %d\n", bd_addr_to_str(address), a2dp_cid, a2dp_local_seid);
#ifdef HAVE_BTSTACK_STDIN
            // use address for outgoing connections
            memcpy(device_addr, address, 6);
#endif
            break;
        
#ifdef ENABLE_AVDTP_ACCEPTOR_EXPLICIT_START_STREAM_CONFIRMATION
        case A2DP_SUBEVENT_START_STREAM_REQUESTED:
            printf("A2DP  Sink      : Explicit Accept to start stream, local_seid 0x%02x\n", a2dp_subevent_start_stream_requested_get_local_seid(packet));
            a2dp_sink_start_stream_accept(a2dp_cid, a2dp_local_seid);
            break;
#endif
        case A2DP_SUBEVENT_STREAM_STARTED:
            printf("A2DP  Sink      : Stream started\n");
            // audio stream is started when buffer reaches minimal level
            break;
        
        case A2DP_SUBEVENT_STREAM_SUSPENDED:
            printf("A2DP  Sink      : Stream paused\n");
            media_processing_pause();
            break;
        
        case A2DP_SUBEVENT_STREAM_RELEASED:
            printf("A2DP  Sink      : Stream released\n");
            media_processing_close();
            break;
        
        case A2DP_SUBEVENT_SIGNALING_CONNECTION_RELEASED:
            printf("A2DP  Sink      : Signaling connection released\n");
            media_processing_close();
            break;
        
        default:
            printf("A2DP  Sink      : Not parsed 0x%02x\n", packet[2]);
            break; 
    }
}

#ifdef HAVE_BTSTACK_STDIN
static void show_usage(void){
    bd_addr_t      iut_address;
    gap_local_bd_addr(iut_address);
    printf("\n--- Bluetooth AVDTP Sink/AVRCP Connection Test Console %s ---\n", bd_addr_to_str(iut_address));
    printf("b      - AVDTP Sink create  connection to addr %s\n", bd_addr_to_str(device_addr));
    printf("B      - AVDTP Sink disconnect\n");
    printf("c      - AVRCP create connection to addr %s\n", bd_addr_to_str(device_addr));
    printf("C      - AVRCP disconnect\n");

    printf("w - delay report\n");

    printf("\n--- Bluetooth AVRCP Commands %s ---\n", bd_addr_to_str(iut_address));
    printf("O - get play status\n");
    printf("j - get now playing info\n");
    printf("k - play\n");
    printf("K - stop\n");
    printf("L - pause\n");
    printf("u - start fast forward\n");
    printf("U - stop  fast forward\n");
    printf("n - start rewind\n");
    printf("N - stop rewind\n");
    printf("i - forward\n");
    printf("I - backward\n");
    printf("M - mute\n");
    printf("r - skip\n");
    printf("q - query repeat and shuffle mode\n");
    printf("v - repeat single track\n");
    printf("x - repeat all tracks\n");
    printf("X - disable repeat mode\n");
    printf("z - shuffle all tracks\n");
    printf("Z - disable shuffle mode\n");

    printf("a/A - register/deregister TRACK_CHANGED\n");
    printf("R/P - register/deregister PLAYBACK_POS_CHANGED\n");

    printf("s/S - send/release long button press REWIND\n");

    printf("\n--- Volume and Battery Control ---\n");
    printf("t - volume up   for 10 percent\n");
    printf("T - volume down for 10 percent\n");
    printf("V - toggle Battery status from AVRCP_BATTERY_STATUS_NORMAL to AVRCP_BATTERY_STATUS_FULL_CHARGE\n");
    printf("---\n");
}
#endif

#ifdef HAVE_BTSTACK_STDIN
static void stdin_process(char cmd){
    uint8_t status = ERROR_CODE_SUCCESS;
    uint8_t volume;
    avrcp_battery_status_t old_battery_status;

    switch (cmd){
        case 'b':
            status = a2dp_sink_establish_stream(device_addr, a2dp_local_seid, &a2dp_cid);
            printf(" - Create AVDTP connection to addr %s, and local seid %d, expected cid 0x%02x.\n", bd_addr_to_str(device_addr), a2dp_local_seid, a2dp_cid);
            break;
        case 'B':
            printf(" - AVDTP disconnect from addr %s.\n", bd_addr_to_str(device_addr));
            a2dp_sink_disconnect(a2dp_cid);
            break;
        case 'c':
            printf(" - Create AVRCP connection to addr %s.\n", bd_addr_to_str(device_addr));
            status = avrcp_connect(device_addr, &avrcp_cid);
            break;
        case 'C':
            printf(" - AVRCP disconnect from addr %s.\n", bd_addr_to_str(device_addr));
            status = avrcp_disconnect(avrcp_cid);
            break;
        
        case '\n':
        case '\r':
            break;
        case 'w':
            printf("Send delay report\n");
            avdtp_sink_delay_report(a2dp_cid, a2dp_local_seid, 100);
            break;
        // Volume Control
        case 't':
            volume_percentage = volume_percentage <= 90 ? volume_percentage + 10 : 100;
            volume = volume_percentage * 127 / 100;
            printf(" - volume up   for 10 percent, %d%% (%d) \n", volume_percentage, volume);
            status = avrcp_target_volume_changed(avrcp_cid, volume);
            avrcp_volume_changed(volume);
            break;
        case 'T':
            volume_percentage = volume_percentage >= 10 ? volume_percentage - 10 : 0;
            volume = volume_percentage * 127 / 100;
            printf(" - volume down for 10 percent, %d%% (%d) \n", volume_percentage, volume);
            status = avrcp_target_volume_changed(avrcp_cid, volume);
            avrcp_volume_changed(volume);
            break;
        case 'V':
            old_battery_status = battery_status;

            if (battery_status < AVRCP_BATTERY_STATUS_FULL_CHARGE){
                battery_status = (avrcp_battery_status_t)((uint8_t) battery_status + 1);
            } else {
                battery_status = AVRCP_BATTERY_STATUS_NORMAL;
            }
            printf(" - toggle battery value, old %d, new %d\n", old_battery_status, battery_status);
            status = avrcp_target_battery_status_changed(avrcp_cid, battery_status);
            break;
        case 'O':
            printf(" - get play status\n");
            status = avrcp_controller_get_play_status(avrcp_cid);
            break;
        case 'j':
            printf(" - get now playing info\n");
            status = avrcp_controller_get_now_playing_info(avrcp_cid);
            break;
        case 'k':
            printf(" - play\n");
            status = avrcp_controller_play(avrcp_cid);
            break;
        case 'K':
            printf(" - stop\n");
            status = avrcp_controller_stop(avrcp_cid);
            break;
        case 'L':
            printf(" - pause\n");
            status = avrcp_controller_pause(avrcp_cid);
            break;
        case 'u':
            printf(" - start fast forward\n");
            status = avrcp_controller_press_and_hold_fast_forward(avrcp_cid);
            break;
        case 'U':
            printf(" - stop fast forward\n");
            status = avrcp_controller_release_press_and_hold_cmd(avrcp_cid);
            break;
        case 'n':
            printf(" - start rewind\n");
            status = avrcp_controller_press_and_hold_rewind(avrcp_cid);
            break;
        case 'N':
            printf(" - stop rewind\n");
            status = avrcp_controller_release_press_and_hold_cmd(avrcp_cid);
            break;
        case 'i':
            printf(" - forward\n");
            status = avrcp_controller_forward(avrcp_cid); 
            break;
        case 'I':
            printf(" - backward\n");
            status = avrcp_controller_backward(avrcp_cid);
            break;
        case 'M':
            printf(" - mute\n");
            status = avrcp_controller_mute(avrcp_cid);
            break;
        case 'r':
            printf(" - skip\n");
            status = avrcp_controller_skip(avrcp_cid);
            break;
        case 'q':
            printf(" - query repeat and shuffle mode\n");
            status = avrcp_controller_query_shuffle_and_repeat_modes(avrcp_cid);
            break;
        case 'v':
            printf(" - repeat single track\n");
            status = avrcp_controller_set_repeat_mode(avrcp_cid, AVRCP_REPEAT_MODE_SINGLE_TRACK);
            break;
        case 'x':
            printf(" - repeat all tracks\n");
            status = avrcp_controller_set_repeat_mode(avrcp_cid, AVRCP_REPEAT_MODE_ALL_TRACKS);
            break;
        case 'X':
            printf(" - disable repeat mode\n");
            status = avrcp_controller_set_repeat_mode(avrcp_cid, AVRCP_REPEAT_MODE_OFF);
            break;
        case 'z':
            printf(" - shuffle all tracks\n");
            status = avrcp_controller_set_shuffle_mode(avrcp_cid, AVRCP_SHUFFLE_MODE_ALL_TRACKS);
            break;
        case 'Z':
            printf(" - disable shuffle mode\n");
            status = avrcp_controller_set_shuffle_mode(avrcp_cid, AVRCP_SHUFFLE_MODE_OFF);
            break;
        case 'a':
            printf("AVRCP: enable notification TRACK_CHANGED\n");
            avrcp_controller_enable_notification(avrcp_cid, AVRCP_NOTIFICATION_EVENT_TRACK_CHANGED);
            break;
        case 'A':
            printf("AVRCP: disable notification TRACK_CHANGED\n");
            avrcp_controller_disable_notification(avrcp_cid, AVRCP_NOTIFICATION_EVENT_TRACK_CHANGED);
            break;
        case 'R':
            printf("AVRCP: enable notification PLAYBACK_POS_CHANGED\n");
            avrcp_controller_enable_notification(avrcp_cid, AVRCP_NOTIFICATION_EVENT_PLAYBACK_POS_CHANGED);
            break;
        case 'P':
            printf("AVRCP: disable notification PLAYBACK_POS_CHANGED\n");
            avrcp_controller_disable_notification(avrcp_cid, AVRCP_NOTIFICATION_EVENT_PLAYBACK_POS_CHANGED);
            break;
         case 's':
            printf("AVRCP: send long button press REWIND\n");
            avrcp_controller_start_press_and_hold_cmd(avrcp_cid, AVRCP_OPERATION_ID_REWIND);
            break;
        case 'S':
            printf("AVRCP: release long button press REWIND\n");
            avrcp_controller_release_press_and_hold_cmd(avrcp_cid);
            break;
        default:
            show_usage();
            return;
    }
    if (status != ERROR_CODE_SUCCESS){
        printf("Could not perform command, status 0x%02x\n", status);
    }
}
#endif









//█████████████████████████████████████████████████




//█████████████████████████████████████████████████

void BLUETOOTH_INIT() {
//--------------------------------------------------------------------------------
///~45kB
  for (uint8_t tmp=0;tmp<UNI_HID_DEVICE_MAX_DEVICES;tmp++) {
    g_devices[tmp]=(uni_hid_device_s*)ps_malloc(sizeof(uni_hid_device_s)); 
    memset(g_devices[tmp], 0, sizeof(uni_hid_device_s)); ///
  }
//--------------------------------------------------------------------------------
///~22kB
  hci_ringbuffer_storage=(uint8_t*)ps_malloc(HCI_HOST_ACL_PACKET_NUM   * (2 + 1 + HCI_ACL_HEADER_SIZE + HCI_HOST_ACL_PACKET_LEN) +
                                      HCI_HOST_SCO_PACKET_NUM   * (2 + 1 + HCI_SCO_HEADER_SIZE + HCI_HOST_SCO_PACKET_LEN) +
                                      MAX_NR_HOST_EVENT_PACKETS * (2 + 1 + HCI_EVENT_BUFFER_SIZE));  
  memset(hci_ringbuffer_storage, 0, HCI_HOST_ACL_PACKET_NUM   * (2 + 1 + HCI_ACL_HEADER_SIZE + HCI_HOST_ACL_PACKET_LEN) +
                                      HCI_HOST_SCO_PACKET_NUM   * (2 + 1 + HCI_SCO_HEADER_SIZE + HCI_HOST_SCO_PACKET_LEN) +
                                      MAX_NR_HOST_EVENT_PACKETS * (2 + 1 + HCI_EVENT_BUFFER_SIZE)); ///
//--------------------------------------------------------------------------------
///~6kB
  sbc_frame_storage=(uint8_t*)ps_malloc((OPTIMAL_FRAMES_MAX + ADDITIONAL_FRAMES) * MAX_SBC_FRAME_SIZE); ///
  decoded_audio_storage=(uint8_t*)ps_malloc((128+16) * BYTES_PER_FRAME);

  sdp_avdtp_sink_service_buffer=(uint8_t*)ps_malloc(150);
  sdp_avrcp_target_service_buffer=(uint8_t*)ps_malloc(150);
  sdp_avrcp_controller_service_buffer=(uint8_t*)ps_malloc(200);
  device_id_sdp_service_buffer=(uint8_t*)ps_malloc(100);
  avrcp_subevent_value=(uint8_t*)ps_malloc(255);
//--------------------------------------------------------------------------------
///~2kB    
  btstack_audio_buffer=(uint8_t*)ps_malloc(DMA_BUFFER_SAMPLES * BYTES_PER_SAMPLE_STEREO); ///
  printf("btstack_audio_buffer size: %d Bytes\n",DMA_BUFFER_SAMPLES * BYTES_PER_SAMPLE_STEREO);
//--------------------------------------------------------------------------------




//--------------------------------------------------------------------------------
  btstack_init();
//--------------------------------------------------------------------------------
  
  
  uni_platform_init(NULL, NULL);
  uni_hid_device_init(); //BT HID init
  ///uni_bluetooth_init();
//--------------------------------------------------------------------------------
    // register for HCI events
    BLUEPAD_hci_event_callback_registration.callback = &BLUEPAD_packet_handler; ///
    hci_add_event_handler(&BLUEPAD_hci_event_callback_registration); ///

    // enabled EIR
    hci_set_inquiry_mode(INQUIRY_MODE_RSSI_AND_EIR);

    // btstack_stdin_setup(stdin_process);
    hci_set_master_slave_policy(HCI_ROLE_MASTER);


///    gap_set_security_level((gap_security_level_t)2); ///BLUETOOTH KEYBOARDS USES SECURED CONNECTIONS
if (Bluetooth_default_security_level==10) {
  printf("\n===> SETTING DEFAULT BLUETOOTH SECURITY LEVEL 0\n\n");
  gap_secure_connections_enable(false);
  gap_set_security_level((gap_security_level_t)0);
}
else if (Bluetooth_default_security_level==11) {
  printf("\n===> SETTING DEFAULT BLUETOOTH SECURITY LEVEL 1\n\n");
  gap_set_security_level((gap_security_level_t)1);
}
else if (Bluetooth_default_security_level==12) { 
  printf("\n===> SETTING DEFAULT BLUETOOTH SECURITY LEVEL 2\n\n");
  gap_set_security_level((gap_security_level_t)2);
}
else if (Bluetooth_default_security_level==13) { 
  printf("\n===> SETTING DEFAULT BLUETOOTH SECURITY LEVEL 3\n\n");
  gap_set_security_level((gap_security_level_t)3);
}
else if (Bluetooth_default_security_level==14) {
  printf("\n===> SETTING DEFAULT BLUETOOTH SECURITY LEVEL 4\n\n");
  gap_set_security_level((gap_security_level_t)4);
} else {
  printf("\n===> BLUETOOTH SECURITY LEVEL NOT SET\n\n");  

    // It seems that with gap_security_level(0) all gamepads work except Nintendo Switch Pro controller.
#ifndef CONFIG_BLUEPAD32_GAP_SECURITY
    gap_set_security_level((gap_security_level_t)0); ///
#endif

}
    
    // Allow sniff mode requests by HID device and support role switch
    gap_set_default_link_policy_settings(LM_LINK_POLICY_ENABLE_SNIFF_MODE | LM_LINK_POLICY_ENABLE_ROLE_SWITCH);

    // Using a minimum of 7 bytes needed for Nintendo Wii / Wii U controllers.
    // See: https://github.com/bluekitchen/btstack/issues/299
    gap_set_required_encryption_key_size(7);

    int security_level = gap_get_security_level();
    logi("Gap security level: %d\n", security_level);

    l2cap_register_service(BLUEPAD_packet_handler, PSM_HID_INTERRUPT, L2CAP_CHANNEL_MTU, (gap_security_level_t)security_level); ///
    l2cap_register_service(BLUEPAD_packet_handler, PSM_HID_CONTROL, L2CAP_CHANNEL_MTU, (gap_security_level_t)security_level); ///
    l2cap_init();

#ifdef ENABLE_BLE
    // register for events from Security Manager
    BLUEPAD_sm_event_callback_registration.callback = &sm_packet_handler; ///
    sm_add_event_handler(&BLUEPAD_sm_event_callback_registration); ///

    // setup LE device db
    le_device_db_init();
    sm_init();
    gatt_client_init();
#endif  // ENABLE_BLE

    // Disable stdout buffering
    setbuf(stdout, NULL);


//--------------------------------------------------------------------------------
  gap_set_allow_role_switch(true); ///YES THIS
  gap_set_local_name("NCAT_SPEAKER 00:00:00:00:00:00"); 
  ///gap_set_class_of_device(0x200408); //headset ID
  ///gap_discoverable_control(1); ///
  gap_ssp_set_enable(1); ///
  gap_ssp_set_auto_accept(1); ///
  ///gap_secure_connections_enable(true); ///enable secured connections (not set by default)
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------    
  ///a2dp_and_avrcp_setup();
//--------------------------------------------------------------------------------    
  hci_power_control(HCI_POWER_ON); // Turn on the device 
//--------------------------------------------------------------------------------

//========================================================================================  
  
  BLUETOOTH_APP=2;
  
}

#endif
