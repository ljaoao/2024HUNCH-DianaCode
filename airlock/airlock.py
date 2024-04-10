from hub import port
import motor
import color
import color_sensor
import runloop

async def main():
    if color_sensor.color(port.F) == color.RED:
        await motor.run_for_degrees(port.C, 280, 360)
        await runloop.sleep_ms(2000)
        await motor.run_for_degrees(port.C, -280, 360)
        await runloop.sleep_ms(2000)
        await motor.run_for_degrees(port.A, -280, 360)
        await runloop.sleep_ms(2000)
        await motor.run_for_degrees(port.A, 280, 360)
        await runloop.sleep_ms(4000)
    if color_sensor.color(port.F) == color.GREEN:
        await motor.run_for_degrees(port.A, -280, 360)
        await runloop.sleep_ms(2000)
        await motor.run_for_degrees(port.A, 280, 360)
        await runloop.sleep_ms(2000)
        await motor.run_for_degrees(port.C, 280, 360)
        await runloop.sleep_ms(2000)
        await motor.run_for_degrees(port.C, -280, 360)
        await runloop.sleep_ms(4000)


while True:
    runloop.run(main())