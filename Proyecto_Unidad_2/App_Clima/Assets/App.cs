using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.Text;

public class App : MonoBehaviour
{
    public Controller serialController;
    private float timer = 0.0f;
    private float waitTime = 1f;
    private Transform objTransform;
    private Vector3 scaleChange;

    public Text segundo;
    public Text minuto;
    public Text hora;
    public Text diaSemana;
    public Text diaMes;
    public Text mes;
    public Text año;

    public Text humedad;
    public Text temperatura;
    public Text altitud;
    public Text presion;

    public



    // Initialization
    void Start()
    {
        serialController = GameObject.Find("SerialController").GetComponent<Controller>();
        objTransform = GetComponent<Transform>();

    }

    // Executed each frame
    void Update()
    {

        //---------------------------------------------------------------------
        // Send data
        //---------------------------------------------------------------------
        if (Input.GetKeyUp(KeyCode.Q))
        {

            serialController.SendSerialMessage(new byte[] { 0x73 });
        }

        timer += Time.deltaTime;
        if (timer > waitTime)
        {
            timer = timer - waitTime;

            serialController.SendSerialMessage(new byte[] { 0x73 });
        }


        byte[] message = serialController.ReadSerialMessage();
        byte[] cadena = new byte[1024];

        if (message == null)
            return;

        byte seconds = message[0];
        byte minuts = message[1];
        byte hours = message[2];
        byte dayOfWeek = message[3];
        byte dayOfMonth = message[4];
        byte month = message[5];
        byte year = message[6];

        byte[] arr_temp = new[] { message[7], message[8], message[9], message[10] };
        byte[] arr_pres = new[] { message[11], message[12], message[13], message[14] };
        byte[] arr_alti = new[] { message[15], message[16], message[17], message[18] };
        byte[] arr_humi = new[] { message[19], message[20], message[21], message[22] };

        float f_temperatura = System.BitConverter.ToSingle(arr_temp, 0);
        float f_presion = System.BitConverter.ToSingle(arr_pres, 0);
        float f_altitud = System.BitConverter.ToSingle(arr_alti, 0);
        float f_humedad = System.BitConverter.ToSingle(arr_humi, 0);

        segundo.text = seconds.ToString();
        minuto.text = minuts.ToString();
        hora.text = hours.ToString();
        diaSemana.text = dayOfWeek.ToString();
        diaMes.text = dayOfMonth.ToString();
        mes.text = month.ToString();
        año.text = year.ToString();

        temperatura.text = f_temperatura.ToString();
        presion.text = f_presion.ToString();
        altitud.text = f_altitud.ToString();
        humedad.text = f_humedad.ToString();

        Debug.Log(" Seconds " + message[0] + " minuts " + message[1] + " hours " + message[2] + " dayOfWeek " +
             message[3] + " dayOfMonth " + message[4] + " month " + message[5] + " year " + message[6] + " temperature " +
              f_temperatura + " pressure " + f_presion + " altitude " + f_altitud + " humidity " + f_humedad);

    }
}