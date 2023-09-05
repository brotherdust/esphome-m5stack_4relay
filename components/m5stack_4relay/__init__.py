import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c
from esphome.const import CONF_ID

DEPENDENCIES = ["i2c"]
MULTI_CONF = True
CONF_STORE_IN_EEPROM = "store_in_eeprom"


m5stack_4relay_ns = cg.esphome_ns.namespace("m5stack_4relay")
M5STACK4RELAYComponent = m5stack_4relay_ns.class_(
    "M5STACK4RELAYComponent", cg.Component, i2c.I2CDevice
)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(M5STACK4RELAYComponent),
            cv.Optional(CONF_STORE_IN_EEPROM, default=False): cv.boolean,
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(i2c.i2c_device_schema(0x26))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID], config[CONF_STORE_IN_EEPROM])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
