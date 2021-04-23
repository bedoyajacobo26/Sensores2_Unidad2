using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class CONFIGURACION : MonoBehaviour
{
    public InputField COMesp32;
    public InputField BResp32;

    public string val_COMesp32;
    public string val_BResp32;

    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        val_COMesp32 = COMesp32.text;
        val_BResp32 = BResp32.text;

    }
    void Awake()
    {
        GameObject[] DontDestroy = GameObject.FindGameObjectsWithTag("DD");

        if (DontDestroy.Length > 1)
        {
            Destroy(this.gameObject);
        }

        DontDestroyOnLoad(this.gameObject);
    }

    public void Jugar()
    {
        SceneManager.LoadScene("SampleScene");
    }
}
